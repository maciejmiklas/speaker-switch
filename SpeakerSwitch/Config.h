/*
   Licensed to the Apache Software Foundation (ASF) under one or more
   contributor license agreements.  See the NOTICE file distributed with
   this work for additional information regarding copyright ownership.
   The ASF licenses this file to You under the Apache License, Version 2.0
   (the "License"); you may not use this file except in compliance with
   the License.  You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <avr/power.h>


// ######## DIGITAL PINs ########
const static uint8_t APIN_D1 = 1;
const static uint8_t APIN_D2 = 2;
const static uint8_t APIN_D3 = 3;
const static uint8_t APIN_D4 = 4;
const static uint8_t APIN_D5 = 5;
const static uint8_t APIN_D6 = 6;
const static uint8_t APIN_D7 = 7;
const static uint8_t APIN_D8 = 8;
const static uint8_t APIN_D9 = 9;
const static uint8_t APIN_D10 = 10;
const static uint8_t APIN_D11 = 11;
const static uint8_t APIN_D12 = 12;

// ######## ANALOG PINs ########
const static uint8_t APIN_A0 = 0;
const static uint8_t APIN_A1 = 1; // BT_PIN_OK
const static uint8_t APIN_A2 = 2; // BT_PIN_CANCEL
const static uint8_t APIN_A3 = 3; // BT_PIN_MENU
const static uint8_t APIN_A4 = 4;
const static uint8_t APIN_A5 = 5;

// ######## ArdLog(AL) ########
const static uint32_t AL_SERIAL_SPEED = 115200;

/** Buffer size for sprintf-template passed as first argument to log method. */
const static uint8_t AL_PGBUF_SIZE = 64;

/** Buffer size for created message. */
const static uint8_t AL_SBUF_SIZE = 96;

// ######## Buttons(BT) ########
const static uint8_t BT_PIN_MENU = APIN_A3;
const static uint8_t BT_PIN_OK = APIN_A1;
const static uint8_t BT_PIN_CANCEL = APIN_A2;
const static uint8_t BT_PRESS_MS = 20;

#endif  // CONFIG_H
