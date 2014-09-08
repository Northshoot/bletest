
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
		radio_ack_pending = true;

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
  randomNum();
  TCNT1H = 11;    // Approx 4000 ms - Reload
  TCNT1L = 0;
  TIFR1  = 0x00;    // timer1 int flag reg: clear timer overflow flag
};



void setup(void)
{
  Serial.begin(115200);


  Serial.println(F("Arduino setup"));

  /**
  Point ACI data structures to the the setup data that the nRFgo studio generated for the nRF8001
  */
  if (NULL != services_pipe_type_mapping)
  {
    aci_state.aci_setup_info.services_pipe_type_mapping = &services_pipe_type_mapping[0];
  }
  else
  {
    aci_state.aci_setup_info.services_pipe_type_mapping = NULL;
  }
  aci_state.aci_setup_info.number_of_pipes    = NUMBER_OF_PIPES;
  aci_state.aci_setup_info.setup_msgs         = setup_msgs;
  aci_state.aci_setup_info.num_setup_msgs     = NB_SETUP_MESSAGES;

  //Tell the ACI library, the MCU to nRF8001 pin connections
  aci_state.aci_pins.board_name = BOARD_DEFAULT; //REDBEARLAB_SHIELD_V1_1 See board.h for details
  aci_state.aci_pins.reqn_pin   = 9;
  aci_state.aci_pins.rdyn_pin   = 8;
  aci_state.aci_pins.mosi_pin   = MOSI;
  aci_state.aci_pins.miso_pin   = MISO;
  aci_state.aci_pins.sck_pin    = SCK;

  aci_state.aci_pins.spi_clock_divider      = SPI_CLOCK_DIV8;//SPI_CLOCK_DIV8  = 2MHz SPI speed
                                                             //SPI_CLOCK_DIV16 = 1MHz SPI speed

  aci_state.aci_pins.reset_pin              = 4;
  aci_state.aci_pins.active_pin             = UNUSED;
  aci_state.aci_pins.optional_chip_sel_pin  = UNUSED;

  aci_state.aci_pins.interface_is_interrupt = false;
  aci_state.aci_pins.interrupt_number       = UNUSED;

  /** We reset the nRF8001 here by toggling the RESET line connected to the nRF8001
   *  and initialize the data structures required to setup the nRF8001
   */
  //The second parameter is for turning debug printing on for the ACI Commands and Events so they be printed on the Serial
  lib_aci_init(&aci_state, false);

}



void loop()
{
	ble_net_loop();
}
