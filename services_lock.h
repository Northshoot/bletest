/* 
* Copyright (c) 2013, Nordic Semiconductor ASA
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
* 
* - Redistributions of source code must retain the above copyright notice, this
*   list of conditions and the following disclaimer.
* 
* - Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
* 
* - The name of Nordic Semiconductor ASA may not be used to endorse or promote
*   products derived from this software without specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
* This file is autogenerated by nRFgo Studio 1.16.1.3119 
*/

#ifndef SETUP_MESSAGES_H__
#define SETUP_MESSAGES_H__

#include "hal_platform.h" 
#include "aci.h"

// You have now chosen to upload the configuration to OTP on the device.
// This will result in a device that you can not modify afterwards. If this is your intention,
// remove this comment and the #error below
#error Generating configuration for OTP. Please verify usage by removing this error message from include file.

#define SETUP_ID 0
#define SETUP_FORMAT 3 /** nRF8001 D */
#define ACI_DYNAMIC_DATA_SIZE 127

/* Service: Larry Service - Characteristic: RandomNumber - Pipe: TX */
#define PIPE_LARRY_SERVICE_RANDOMNUMBER_TX          1
#define PIPE_LARRY_SERVICE_RANDOMNUMBER_TX_MAX_SIZE 1

/* Service: Larry Service - Characteristic: RandomNumber - Pipe: RX */
#define PIPE_LARRY_SERVICE_RANDOMNUMBER_RX          2
#define PIPE_LARRY_SERVICE_RANDOMNUMBER_RX_MAX_SIZE 1

/* Service: Larry Service - Characteristic: RandomNumber - Pipe: SET */
#define PIPE_LARRY_SERVICE_RANDOMNUMBER_SET          3
#define PIPE_LARRY_SERVICE_RANDOMNUMBER_SET_MAX_SIZE 1

/* Service: Lars Service - Characteristic: RandomSum - Pipe: TX_ACK */
#define PIPE_LARS_SERVICE_RANDOMSUM_TX_ACK          4
#define PIPE_LARS_SERVICE_RANDOMSUM_TX_ACK_MAX_SIZE 1

/* Service: Lars Service - Characteristic: RandomSum - Pipe: RX */
#define PIPE_LARS_SERVICE_RANDOMSUM_RX          5
#define PIPE_LARS_SERVICE_RANDOMSUM_RX_MAX_SIZE 1

/* Service: Lars Service - Characteristic: RandomSum - Pipe: RX_REQ */
#define PIPE_LARS_SERVICE_RANDOMSUM_RX_REQ          6
#define PIPE_LARS_SERVICE_RANDOMSUM_RX_REQ_MAX_SIZE 1


#define NUMBER_OF_PIPES 6

#define SERVICES_PIPE_TYPE_MAPPING_CONTENT {\
  {ACI_STORE_LOCAL, ACI_TX},   \
  {ACI_STORE_LOCAL, ACI_RX},   \
  {ACI_STORE_LOCAL, ACI_SET},   \
  {ACI_STORE_REMOTE, ACI_TX_ACK},   \
  {ACI_STORE_REMOTE, ACI_RX},   \
  {ACI_STORE_REMOTE, ACI_RX_REQ},   \
}

#define GAP_PPCP_MAX_CONN_INT 0xffff /**< Maximum connection interval as a multiple of 1.25 msec , 0xFFFF means no specific value requested */
#define GAP_PPCP_MIN_CONN_INT  0xffff /**< Minimum connection interval as a multiple of 1.25 msec , 0xFFFF means no specific value requested */
#define GAP_PPCP_SLAVE_LATENCY 0
#define GAP_PPCP_CONN_TIMEOUT 0xffff /** Connection Supervision timeout multiplier as a multiple of 10msec, 0xFFFF means no specific value requested */

#define NB_SETUP_MESSAGES 17
#define SETUP_MESSAGES_CONTENT {\
    {0x00,\
        {\
            0x07,0x06,0x00,0x00,0x03,0x02,0x41,0xfe,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x02,0x07,0x01,0x01,0x00,0x00,0x06,0x00,0x01,\
            0xc1,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x1c,0x00,0x00,0x01,0x66,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
            0x00,0x00,0x04,0x11,0x00,0x00,0x04,0x11,0x03,0x90,0x00,0xff,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x38,0xff,0xff,0x02,0x58,0x0a,0x05,0x00,0x00,0x04,0x11,0x00,0x00,0x04,0x11,0x00,0x00,\
            0x04,0x11,0x00,0x00,0x04,0x11,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x05,0x06,0x10,0x54,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x00,0x04,0x04,0x02,0x02,0x00,0x01,0x28,0x00,0x01,0x00,0x18,0x04,0x04,0x05,0x05,0x00,\
            0x02,0x28,0x03,0x01,0x02,0x03,0x00,0x00,0x2a,0x04,0x04,0x14,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x1c,0x09,0x00,0x03,0x2a,0x00,0x01,0x4c,0x61,0x72,0x72,0x79,0x52,0x57,0x52,0x4c,0x69,\
            0x2e,0x63,0x6f,0x6d,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x38,0x05,0x05,0x00,0x04,0x28,0x03,0x01,0x02,0x05,0x00,0x01,0x2a,0x06,0x04,0x03,0x02,\
            0x00,0x05,0x2a,0x01,0x01,0x00,0x00,0x04,0x04,0x05,0x05,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x54,0x06,0x28,0x03,0x01,0x02,0x07,0x00,0x04,0x2a,0x06,0x04,0x09,0x08,0x00,0x07,0x2a,\
            0x04,0x01,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0x04,0x04,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x70,0x02,0x02,0x00,0x08,0x28,0x00,0x01,0x01,0x18,0x04,0x04,0x02,0x02,0x00,0x09,0x28,\
            0x00,0x01,0x11,0x11,0x04,0x04,0x05,0x05,0x00,0x0a,0x28,0x03,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x8c,0x01,0x16,0x0b,0x00,0x22,0x22,0x56,0x14,0x02,0x01,0x00,0x0b,0x22,0x22,0x01,0xff,\
            0x06,0x04,0x08,0x07,0x00,0x0c,0x29,0x04,0x01,0x04,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x13,0x06,0x20,0xa8,0x00,0x01,0x00,0x00,0x46,0x14,0x03,0x02,0x00,0x0d,0x29,0x02,0x01,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x0d,0x06,0x30,0x00,0x66,0x66,0x01,0x01,0x01,0x18,0x01,0x01,0x02,0x01,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x40,0x00,0x22,0x22,0x01,0x00,0x8a,0x04,0x00,0x0b,0x00,0x0d,0x77,0x77,0x01,0x00,0x4c,0x04,\
            0x00,0x00,0x00,0x00,0x2a,0x05,0x01,0x00,0x10,0x04,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x05,0x06,0x40,0x1c,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x0c,0x06,0x60,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x06,0x06,0xf0,0x00,0x83,0x15,0xa7,\
        },\
    },\
}

#endif