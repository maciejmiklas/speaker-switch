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

// ######## DIGITAL PINs ########
const static uint8_t DPIN_1 = 1;
const static uint8_t DPIN_2 = 2; // LC_LCD_D7
const static uint8_t DPIN_3 = 3; // LC_LCD_D6
const static uint8_t DPIN_4 = 4; // LC_LCD_D5
const static uint8_t DPIN_5 = 5; // LC_LCD_D4
const static uint8_t DPIN_6 = 6; // SU_RELAY_PIN
const static uint8_t DPIN_7 = 7; // LC_LCD_K
const static uint8_t DPIN_8 = 8; // SR_RELAY_PIN
const static uint8_t DPIN_9 = 9; // IR_RECEIVE_PIN
const static uint8_t DPIN_10 = 10;
const static uint8_t DPIN_11 = 11; // LC_LCD_E
const static uint8_t DPIN_12 = 12; // LC_LCD_RS

// ######## ANALOG PINs ########
const static uint8_t APIN_0 = A0; // LCD
const static uint8_t APIN_1 = A1; // BT_PIN_OK
const static uint8_t APIN_2 = A2; // BT_PIN_CANCEL
const static uint8_t APIN_3 = A3; // BT_PIN_MENU
const static uint8_t APIN_4 = A4; // YT_TRIG_PIN
const static uint8_t APIN_5 = A5; 
const static uint8_t APIN_6 = A6;
const static uint8_t APIN_7 = A7;

// ######## ArdLog(AL) ########
const static uint32_t AL_SERIAL_SPEED = 115200;

/** Buffer size for sprintf-template passed as first argument to log method. */
const static uint8_t AL_PGBUF_SIZE = 64;

/** Buffer size for created message. */
const static uint8_t AL_SBUF_SIZE = 96;

// ######## Buttons(BT) ########
const static uint8_t BT_PIN_MENU = PIN_A3;
const static uint8_t BT_PIN_OK = PIN_A1;
const static uint8_t BT_PIN_CANCEL = PIN_A2;
const static uint8_t BT_PRESS_MS = 50;
const static uint8_t BT_REP_PRESS_MS = 200;

// ######## YamahaTrigger(YT) ########
/* Number of milliseconds that the 12V amp reading has to remain low or high to flip the state. */
const static uint8_t YT_STATE_CHANGE_MS = 100;
const static uint8_t YT_TRIG_PIN = APIN_4;

// ######## SpeakerRelay(SR) ########
const static uint8_t SR_RELAY_PIN = DPIN_8;

// ######## SubRelay(SU) ########
const static uint8_t SU_RELAY_PIN = DPIN_6;

// ######## IrReceiver(IR) ########
const static uint8_t IR_RECEIVE_PIN = DPIN_9;
const static uint16_t IR_STATE_CHANGE_MS = 1000;

// ######## LcdDisplay(LC) ########
const static uint8_t LC_LCD_RS = DPIN_12;
const static uint8_t LC_LCD_E = DPIN_11;

const static uint8_t LC_LCD_D4 = DPIN_5;
const static uint8_t LC_LCD_D5 = DPIN_4;
const static uint8_t LC_LCD_D6 = DPIN_3;
const static uint8_t LC_LCD_D7 = DPIN_2;

const static uint8_t LC_LCD_K = DPIN_7;

#endif  // CONFIG_H
