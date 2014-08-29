/*
 * basic_setup.h
 *
 *  Created on: Aug 26, 2014
 *      Author: lauril
 */

#ifndef BASIC_SETUP_H_
#define BASIC_SETUP_H_

#include "Arduino.h"
#include "services.h"
#include "lib_aci.h"
#include "aci_setup.h"
#include <SPI.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#ifdef SERVICES_PIPE_TYPE_MAPPING_CONTENT
static services_pipe_type_mapping_t services_pipe_type_mapping[NUMBER_OF_PIPES] =
		SERVICES_PIPE_TYPE_MAPPING_CONTENT;
#else
#define NUMBER_OF_PIPES 0
static services_pipe_type_mapping_t * services_pipe_type_mapping = NULL;
#endif

#define DEFAULT_REQN    9
#define DEFAULT_RDYN    8

#define PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET 4
/*
 Store the nRF8001 setup information generated on the flash of the AVR.
 This reduces the RAM requirements for the nRF8001.
 */
static hal_aci_data_t setup_msgs[NB_SETUP_MESSAGES] PROGMEM =
		SETUP_MESSAGES_CONTENT;
// an aci_struct that will contain
// total initial credits
// current credit
// current state of the aci (setup/standby/active/sleep)
// open remote pipe pending
// close remote pipe pending
// Current pipe available bitmap
// Current pipe closed bitmap
// Current connection interval, slave latency and link supervision timeout
// Current State of the the GATT client (Service Discovery)
static aci_state_t aci_state;

static hal_aci_evt_t aci_data;

static bool radio_ack_pending = false;
static bool timing_change_done = false;


int set_node_up(void);
void Timer1stop(void);
void Timer1start(void);




#endif /* BASIC_SETUP_H_ */
