
#include <SPI.h>
#include "services.h"
#include <lib_aci.h>
#include <aci_setup.h>
#include "networking.h"
#include "InsulinePump.h"


void randomNum(void)
{

	bool rqData ;
	uint8_t data;

	if(readRemoteServiceData(PIPE_GLUCOSE_GLUCOSE_MEASURMENT_RX)){
		data = getData();
		Serial.print(F("Got PIPE_GLUCOSE_GLUCOSE_MEASURMENT_RX"));
		Serial.println(data, HEX);
	}
	if(readRemoteServiceData(PIPE_GLUCOSE_GLUCOSE_MEASUREMENT_CONTEXT_RX)){
		data = getData();
		Serial.print(F("Got PIPE_GLUCOSE_GLUCOSE_MEASUREMENT_CONTEXT_RX"));
		Serial.println(data, HEX);
	}
	if(readRemoteServiceData(PIPE_GLUCOSE_GLUCOSE_FEATURE_RX_REQ)){
		data = getData();
		Serial.print(F("Got PIPE_GLUCOSE_GLUCOSE_FEATURE_RX_REQ"));
		Serial.println(data, HEX);
	}

}

/*** FUNC
Name:       Timer1 ISR
Function:   Handles the Timer1-overflow interrupt
FUNC ***/
ISR(TIMER1_OVF_vect)
{
  randomNum();
  TCNT1H = 0;    // Approx 4000 ms - Reload
  TCNT1L = 11;
  TIFR1  = 0x00;    // timer1 int flag reg: clear timer overflow flag
};






void loop()
{
	ble_net_loop();
}
