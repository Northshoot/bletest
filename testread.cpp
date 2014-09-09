
#include <SPI.h>
#include "services.h"
#include <lib_aci.h>
#include <aci_setup.h>
#include "networking.h"



void randomNum(void)
{
	uint8_t rnd = random(0, 255);

	lib_aci_set_local_data(&aci_state, PIPE_LARRY_SERVICE_RANDOMNUMBER_TX, &rnd,
			sizeof(rnd));
	if (lib_aci_is_pipe_available(&aci_state,
	PIPE_LARRY_SERVICE_RANDOMNUMBER_TX)) {
		//is sending them it is subscribed

		if (lib_aci_send_data(PIPE_LARRY_SERVICE_RANDOMNUMBER_TX, &rnd,
				sizeof(rnd))) {
			Serial.println(F("OK lib send data"));
			aci_state.data_credit_available--;
		} else {
			Serial.println(F("FAIL lib send data"));
		}


	} else {
		Serial.println(F("NOT Sending"));
	}

	Serial.print(F("perform random number: HEX: "));
	Serial.print(rnd, HEX);
	Serial.print(F(" DEC "));
	Serial.print(rnd);
	Serial.println("\n");

}

/*** FUNC
Name:       Timer1 ISR
Function:   Handles the Timer1-overflow interrupt
FUNC ***/
ISR(TIMER1_OVF_vect)
{
  //randomNum();
  TCNT1H = 11;    // Approx 4000 ms - Reload
  TCNT1L = 0;
  TIFR1  = 0x00;    // timer1 int flag reg: clear timer overflow flag
};






void loop()
{
	ble_net_loop();
}
