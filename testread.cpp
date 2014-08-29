/* Copyright (c) 2014, Nordic Semiconductor ASA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 *IMPORTANT: This example still is not compatible with CHIPKIT
 *
 * Click on the "Serial Monitor" button on the Arduino IDE to get reset the Arduino and start the application.
 * The setup() function is called first and is called only one for each reset of the Arduino.
 * The loop() function as the name implies is called in a loop.
 * The setup() and loop() function are called in this way.
 * main()
 *  {
 *   setup();
 *   while(1)
 *   {
 *     loop();
 *   }
 * }
 *
 */
#include "Arduino.h"
#include <SPI.h>
#include "services.h"
#include "lib_aci.h"
#include "aci_setup.h"
#include "basic_setup.h"

#define RND_MAX_SIZE

void perform_random_number(void) {
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

static unsigned char is_connected = 0;
static volatile byte ack = 0;

void aci_loop() {
	static bool setup_required = false;
	// We enter the if statement only when there is a ACI event available to be processed
	if (lib_aci_event_get(&aci_state, &aci_data)) {
		aci_evt_t *aci_evt;
		aci_evt = &aci_data.evt;
		switch (aci_evt->evt_opcode) {
		/* As soon as you reset the nRF8001 you will get an ACI Device Started Event */
		case ACI_EVT_DEVICE_STARTED:
			aci_state.data_credit_total =
					aci_evt->params.device_started.credit_available;
			switch (aci_evt->params.device_started.device_mode) {
			case ACI_DEVICE_SETUP:
				/* When the device is in the setup mode*/
				Serial.println(F("Evt Device Started: Setup"));
				setup_required = true;
				break;
			case ACI_DEVICE_STANDBY:
				Serial.println(F("Evt Device Started: Standby"));
				//Looking for an iPhone by sending radio advertisements
				//When an iPhone connects to us we will get an ACI_EVT_CONNECTED event from the nRF8001
				if (aci_evt->params.device_started.hw_error) {
					delay(20); //Magic number used to make sure the HW error event is handled correctly.
				} else {
					lib_aci_connect(180/* in seconds */,
							0x0050 /* advertising interval 50ms*/);
					Serial.println(F("Advertising started"));
				}
				break;
			}
			break; //ACI Device Started Event

		case ACI_EVT_CMD_RSP:
			//If an ACI command response event comes with an error -> stop
			if (ACI_STATUS_SUCCESS != aci_evt->params.cmd_rsp.cmd_status) {
				//ACI ReadDynamicData and ACI WriteDynamicData will have status codes of
				//TRANSACTION_CONTINUE and TRANSACTION_COMPLETE
				//all other ACI commands will have status code of ACI_STATUS_SCUCCESS for a successful command
				Serial.print(F("ACI Command "));
				Serial.println(aci_evt->params.cmd_rsp.cmd_opcode, HEX);
				Serial.print(F("Evt Cmd respone: Status "));
				Serial.println(aci_evt->params.cmd_rsp.cmd_status, HEX);
			}
			if (ACI_CMD_GET_DEVICE_VERSION
					== aci_evt->params.cmd_rsp.cmd_opcode) {
				//Store the version and configuration information of the nRF8001 in the Hardware Revision String Characteristic
				lib_aci_set_local_data(&aci_state,
						PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET,
						(uint8_t *) &(aci_evt->params.cmd_rsp.params.get_device_version),
						sizeof(aci_evt_cmd_rsp_params_get_device_version_t));
			}
			break;

		case ACI_EVT_CONNECTED:
			is_connected = 1;
			Serial.println(F("Evt Connected"));
			timing_change_done = false;
			aci_state.data_credit_available = aci_state.data_credit_total;
			/*Get the device version of the nRF8001 and store it in the Hardware Revision String*/
			lib_aci_device_version();
			break;

		case ACI_EVT_PIPE_STATUS:
			Serial.println(F("Evt Pipe Status"));
			if (lib_aci_is_pipe_available(&aci_state,
					PIPE_LARRY_SERVICE_RANDOMNUMBER_TX)
					&& (false == timing_change_done)) {
				Serial.println(F("PIPE_LARRY_SERVICE_RANDOMNUMBER_TX"));
				lib_aci_change_timing_GAP_PPCP(); // change the timing on the link as specified in the nRFgo studio -> nRF8001 conf. -> GAP.
												  // Used to increase or decrease bandwidth
				timing_change_done = true;
			} else if (lib_aci_is_pipe_available(&aci_state,
					PIPE_LARRY_SERVICE_RANDOMNUMBER_RX)
					&& (false == timing_change_done)) {
				Serial.println(F("PIPE_LARRY_SERVICE_RANDOMNUMBER_RX"));
				lib_aci_change_timing_GAP_PPCP(); // change the timing on the link as specified in the nRFgo studio -> nRF8001 conf. -> GAP.
												  // Used to increase or decrease bandwidth
				timing_change_done = true;
			} else if (lib_aci_is_pipe_available(&aci_state,
					PIPE_LARRY_SERVICE_RANDOMNUMBER_SET)
					&& (false == timing_change_done)) {
				Serial.println(F("PIPE_LARRY_SERVICE_RANDOMNUMBER_SET"));
				lib_aci_change_timing_GAP_PPCP(); // change the timing on the link as specified in the nRFgo studio -> nRF8001 conf. -> GAP.
												  // Used to increase or decrease bandwidth
				timing_change_done = true;
			} else if (lib_aci_is_pipe_available(&aci_state,
					PIPE_LARS_SERVICE_RANDOMSUM_TX_ACK)
					&& (false == timing_change_done)) {
				Serial.println(
						F(
								"PIPE_LARS_SERVICE_RANDOMSUM_TX_ACKPIPE_LARS_SERVICE_RANDOMSUM_TX_ACK"));
				lib_aci_change_timing_GAP_PPCP(); // change the timing on the link as specified in the nRFgo studio -> nRF8001 conf. -> GAP.
												  // Used to increase or decrease bandwidth
				timing_change_done = true;
			} else if (lib_aci_is_pipe_available(&aci_state,
					PIPE_LARS_SERVICE_RANDOMSUM_RX)
					&& (false == timing_change_done)) {
				Serial.println(F("PIPE_LARS_SERVICE_RANDOMSUM_RX"));
				lib_aci_change_timing_GAP_PPCP(); // change the timing on the link as specified in the nRFgo studio -> nRF8001 conf. -> GAP.
												  // Used to increase or decrease bandwidth
				timing_change_done = true;
			} else if (lib_aci_is_pipe_available(&aci_state,
					PIPE_LARS_SERVICE_RANDOMSUM_RX_REQ)
					&& (false == timing_change_done)) {
				Serial.println(F("PIPE_LARS_SERVICE_RANDOMSUM_RX_REQ"));
				lib_aci_change_timing_GAP_PPCP(); // change the timing on the link as specified in the nRFgo studio -> nRF8001 conf. -> GAP.
												  // Used to increase or decrease bandwidth
				timing_change_done = true;
			} else {
				Serial.println(F("random state???!!!"));
			}

			break;

		case ACI_EVT_TIMING:
			Serial.println(F("Evt link connection interval changed"));
			break;

		case ACI_EVT_DISCONNECTED:
			is_connected = 0;
			ack = 1;
			Serial.println(F("Evt Disconnected/Advertising timed out"));
			lib_aci_connect(30/* in seconds */,
					0x0050 /* advertising interval 100ms*/);
			Serial.println(F("Advertising started"));
			break;

		case ACI_EVT_DATA_RECEIVED:
			Serial.print(F("Pipe Number: "));
			Serial.println(aci_evt->params.data_received.rx_data.pipe_number,
					DEC);
//			for (int i = 0; i < aci_evt->len - 2; i++) {
//				if (rx_buffer_len == MAX_RX_BUFF) {
//					break;
//				} else {
//					if (p_back == &rx_buff[MAX_RX_BUFF]) {
//						p_back = &rx_buff[0];
//					}
//					*p_back = aci_evt->params.data_received.rx_data.aci_data[i];
//					rx_buffer_len++;
//					p_back++;
//				}
//			}
			break;

		case ACI_EVT_DATA_CREDIT:
			aci_state.data_credit_available = aci_state.data_credit_available
					+ aci_evt->params.data_credit.credit;
			Serial.print("ACI_EVT_DATA_CREDIT     ");
			Serial.print("Data Credit available: ");
			Serial.println(aci_state.data_credit_available, DEC);
			ack = 1;
			break;

		case ACI_EVT_PIPE_ERROR:
			//See the appendix in the nRF8001 Product Specication for details on the error codes
			Serial.print(F("ACI Evt Pipe Error: Pipe #:"));
			Serial.print(aci_evt->params.pipe_error.pipe_number, DEC);
			Serial.print(F("  Pipe Error Code: 0x"));
			Serial.println(aci_evt->params.pipe_error.error_code, HEX);

			//Increment the credit available as the data packet was not sent.
			//The pipe error also represents the Attribute protocol Error Response sent from the peer and that should not be counted
			//for the credit.
			if (ACI_STATUS_ERROR_PEER_ATT_ERROR
					!= aci_evt->params.pipe_error.error_code) {
				aci_state.data_credit_available++;
			}
			Serial.print("Data Credit available: ");
			Serial.println(aci_state.data_credit_available, DEC);
			break;

		case ACI_EVT_HW_ERROR:
			Serial.print(F("HW error: "));
			Serial.println(aci_evt->params.hw_error.line_num, DEC);

			for (uint8_t counter = 0; counter <= (aci_evt->len - 3);
					counter++) {
				Serial.write(aci_evt->params.hw_error.file_name[counter]); //uint8_t file_name[20];
			}
			Serial.println();
			lib_aci_connect(180/* in seconds */,
					0x0050 /* advertising interval 50ms*/);
			Serial.println(F("Advertising started"));
			break;
		}
	} else {
		Serial.println(F("No ACI Events available"));
		// No event in the ACI Event queue and if there is no event in the ACI command queue the arduino can go to sleep
		// Arduino can go to sleep now
		// Wakeup from sleep from the RDYN line
	}
	/* setup_required is set to true when the device starts up and enters setup mode.
	 * It indicates that do_aci_setup() should be called. The flag should be cleared if
	 * do_aci_setup() returns ACI_STATUS_TRANSACTION_COMPLETE.
	 */
	if (setup_required) {
		if (SETUP_SUCCESS == do_aci_setup(&aci_state)) {
			setup_required = false;
		}
	} else {
		Serial.println(F("Bummer"));
	}
}

void loop() {
	aci_loop();
}

