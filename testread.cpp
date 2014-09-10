
#include <SPI.h>
#include "services.h"
#include <lib_aci.h>
#include <aci_setup.h>
#include "networking.h"



void randomNum(void)
{
	uint8_t rnd = random(0, 255);
	bool rqData = false;

	if( lib_aci_is_pipe_available(&aci_state,
			PIPE_LARS_SERVICE_RANDOMSUM_RX_REQ) ){
		Serial.println(F("pipe available PIPE_LARS_SERVICE_RANDOMSUM_RX_REQ "));
		rqData = lib_aci_request_data(&aci_state,
			PIPE_LARS_SERVICE_RANDOMSUM_RX_REQ);
		if(rqData)
			Serial.println(F("Requested data on pipe"));
	}
	Serial.println(F("randomNum loop "));

}

/*** FUNC
Name:       Timer1 ISR
Function:   Handles the Timer1-overflow interrupt
FUNC ***/
ISR(TIMER1_OVF_vect)
{
  randomNum();
  TCNT1H = 11;    // Approx 4000 ms - Reload
  TCNT1L = 0;
  TIFR1  = 0x00;    // timer1 int flag reg: clear timer overflow flag
};






void loop()
{
	ble_net_loop();

}
