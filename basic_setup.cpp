#include "basic_setup.h"

#include "Arduino.h"
#include <SPI.h>
#include "services.h"
#include "lib_aci.h"
#include "aci_setup.h"

int set_node_up(void)
{
	return 8;

}

/*** FUNC
 Name:           Timer1start
 Function:       Start timer 1 to interrupt periodically. Call this from
 the Arduino setup() function.
 Description:    The pre-scaler and the timer count divide the timer-counter
 clock frequency to give a timer overflow interrupt rate:

 Interrupt rate =  16MHz / (prescaler * (255 - TCNT2))

 TCCR2B[b2:0]   Prescaler    Freq [KHz], Period [usec] after prescale
 0x0            (TC stopped)     0         0
 0x1                1        16000.        0.0625
 0x2                8         2000.        0.500
 0x3               32          500.        2.000
 0x4               64          250.        4.000
 0x5              128          125.        8.000
 0x6              256           62.5      16.000
 0x7             1024           15.625    64.000
 FUNC ***/

void Timer1start() {

	// Setup Timer1 overflow to fire every 4000ms
	//   period [sec] = (1 / f_clock [sec]) * prescale * (count)
	//                  (1/16000000)  * 1024 * (count) = 4000 ms

	TCCR1B = 0x00;        // Disable Timer1 while we set it up

	TCNT1H = 11;          // Approx 4000ms when prescaler is set to 1024
	TCNT1L = 0;
	TIFR1 = 0x00;        // Timer1 INT Flag Reg: Clear Timer Overflow Flag
	TIMSK1 = 0x01;        // Timer1 INT Reg: Timer1 Overflow Interrupt Enable
	TCCR1A = 0x00;        // Timer1 Control Reg A: Wave Gen Mode normal
	TCCR1B = 0x05;        // Timer1 Control Reg B: Timer Prescaler set to 1024
}

void Timer1stop() {
	TCCR1B = 0x00;
	TIMSK1 = 0x00;
}


uint8_t reqn_pin = DEFAULT_REQN;
uint8_t rdyn_pin = DEFAULT_RDYN;

static unsigned char spi_old;

/* Define how assert should function in the BLE library */
void __ble_assert(const char *file, uint16_t line)
{
    Serial.print("ERROR ");
    Serial.print(file);
    Serial.print(": ");
    Serial.print(line);
    Serial.print("\n");
    while(1);
}

void ble_set_pins(uint8_t reqn, uint8_t rdyn)
{
	reqn_pin = reqn;
    rdyn_pin = rdyn;
}

void ble_begin()
{
    spi_old = SPCR;
    SPI.setBitOrder(LSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    SPI.setDataMode(SPI_MODE0);

     /* Point ACI data structures to the the setup data that the nRFgo studio generated for the nRF8001 */
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

    /*
    Tell the ACI library, the MCU to nRF8001 pin connections.
    The Active pin is optional and can be marked UNUSED
    */
    aci_state.aci_pins.board_name = REDBEARLAB_SHIELD_V1_1; //See board.h for details
    aci_state.aci_pins.reqn_pin   = reqn_pin;
    aci_state.aci_pins.rdyn_pin   = rdyn_pin;
    aci_state.aci_pins.mosi_pin   = MOSI;
    aci_state.aci_pins.miso_pin   = MISO;
    aci_state.aci_pins.sck_pin    = SCK;

    aci_state.aci_pins.spi_clock_divider     = SPI_CLOCK_DIV8;

    aci_state.aci_pins.reset_pin             = UNUSED;
    aci_state.aci_pins.active_pin            = UNUSED;
    aci_state.aci_pins.optional_chip_sel_pin = UNUSED;

    aci_state.aci_pins.interface_is_interrupt	  = false;
    aci_state.aci_pins.interrupt_number			  = 4;//1;

    //We reset the nRF8001 here by toggling the RESET line connected to the nRF8001
    //If the RESET line is not available we call the ACI Radio Reset to soft reset the nRF8001
    //then we initialize the data structures required to setup the nRF8001
    //The second parameter is for turning debug printing on for the ACI Commands and Events so they be printed on the Serial
    lib_aci_init(&aci_state, false);

    SPCR = spi_old;
    SPI.begin();
}
void setup(void) {
	Serial.begin(115200);

	Serial.println(F("Arduino setup"));
	Serial.println(set_node_up());

	ble_begin();

}
