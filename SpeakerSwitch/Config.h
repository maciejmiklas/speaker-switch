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

static constexpr const char *APP_NAME = " Speaker Switch ";
static constexpr const char *VERSION = "     v2.00      ";

// ######## DIGITAL PINs ########
static constexpr uint8_t DIO_0 = 0; //   [PIN:30, PD0] Hardware Serial RX/TX
static constexpr uint8_t DIO_1 = 1; //   [PIN:31, PD1] Hardware Serial RX/TX
static constexpr uint8_t DIO_2 = 2; //   [PIN:32, PD2] LC_LCD_D7
static constexpr uint8_t DIO_3 = 3; //   [PIN:01, PD3] LC_LCD_D6
static constexpr uint8_t DIO_4 = 4; //   [PIN:02, PD4] LC_LCD_D5
static constexpr uint8_t DIO_5 = 5; //   [PIN:09, PD5] LC_LCD_D4
static constexpr uint8_t DIO_6 = 6; //   [PIN:10, PD6] RE_SUB_PIN
static constexpr uint8_t DIO_7 = 7; //   [PIN:11, PD7] LC_LCD_K
static constexpr uint8_t DIO_8 = 8; //   [PIN:12, PB0] RE_SPK_PIN
static constexpr uint8_t DIO_9 = 9; //   [PIN:13, PB1] IR_RECEIVE_PIN
static constexpr uint8_t DIO_10 = 10; // [PIN:14, PB2] LC_LCD_RS
static constexpr uint8_t DIO_11 = 11; // [PIN:15, PB3] LC_LCD_E

// ######## ANALOG PINs ########
static constexpr uint8_t AIO_0 = A0; // LCD BRIGHTNESS
static constexpr uint8_t AIO_1 = A1; // BT_PIN_OK
static constexpr uint8_t AIO_2 = A2; // BT_PIN_CANCEL
static constexpr uint8_t AIO_3 = A3; // BT_PIN_MENU
static constexpr uint8_t AIO_4 = A4; // YT_TRIG_PIN
static constexpr uint8_t AIO_5 = A5; // IR LED
static constexpr uint8_t AIO_6 = A6;
static constexpr uint8_t AIO_7 = A7;

// ######## ArdLog(AL) ########
static constexpr uint32_t AL_SERIAL_SPEED = 115200;

/** Buffer size for sprintf-template passed as first argument to log method. */
static constexpr uint8_t AL_PGBUF_SIZE = 64;

/** Buffer size for created message. */
static constexpr uint8_t AL_SBUF_SIZE = 96;

// ######## Buttons(BT) ########
static constexpr uint8_t BT_PIN_MENU = PIN_A3;
static constexpr uint8_t BT_PIN_OK = PIN_A1;
static constexpr uint8_t BT_PIN_CANCEL = PIN_A2;
static constexpr uint8_t BT_PRESS_MS = 50;
static constexpr uint8_t BT_REP_PRESS_MS = 200;

// ######## YamahaTrigger(YT) ########
/* Number of milliseconds that the 12V amp reading has to remain low or high to flip the state. */
static constexpr uint8_t YT_STATE_CHANGE_MS = 100;
static constexpr uint8_t YT_TRIG_PIN = AIO_4;

// ######## Relay(RE) ########
static constexpr uint8_t RE_SUB_PIN = DIO_6;
static constexpr uint8_t RE_SPK_PIN = DIO_8;

// ######## IrReceiver(IR) ########
static constexpr uint8_t IR_RECEIVE_PIN = DIO_9;
static constexpr uint16_t IR_STATE_CHANGE_MS = 1000;

// ######## LcdDisplay(LC) ########
static constexpr uint8_t LC_LCD_RS = DIO_10;
static constexpr uint8_t LC_LCD_E = DIO_11;

static constexpr uint8_t LC_LCD_D4 = DIO_5;
static constexpr uint8_t LC_LCD_D5 = DIO_4;
static constexpr uint8_t LC_LCD_D6 = DIO_3;
static constexpr uint8_t LC_LCD_D7 = DIO_2;

static constexpr uint8_t LC_LCD_K = DIO_7;

// ######## Display(DS) ########
static constexpr uint16_t DS_INFO_DELAY_MS = 2000;

// ######## SystemStateManager(SM) ########
static constexpr uint16_t SM_IDLE_TIMEOUT_MS = 10000; // 10 seconds

#endif  // CONFIG_H
