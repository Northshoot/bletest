/*
 * networking.h
 *
 *  Created on: Sep 8, 2014
 *      Author: lauril
 */

#ifndef NETWORKING_H_
#define NETWORKING_H_

#include <SPI.h>
#include "services.h"
#include <lib_aci.h>
#include <aci_setup.h>

static services_pipe_type_mapping_t
        services_pipe_type_mapping[NUMBER_OF_PIPES] = SERVICES_PIPE_TYPE_MAPPING_CONTENT;



/*
Store the nRF8001 setup information generated on the flash of the AVR.
This reduces the RAM requirements for the nRF8001.
*/
static hal_aci_data_t setup_msgs[NB_SETUP_MESSAGES] PROGMEM = SETUP_MESSAGES_CONTENT;
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

static bool radio_ack_pending  = false;
static bool timing_change_done = false;

#define MAX_RX_BUFF 64

static uint8_t rx_buff[MAX_RX_BUFF+1];
static uint8_t rx_buffer_len = 0;
static uint8_t *p_before = &rx_buff[0] ;
static uint8_t *p_back = &rx_buff[0];


void ble_net_loop(void);


#endif /* NETWORKING_H_ */
