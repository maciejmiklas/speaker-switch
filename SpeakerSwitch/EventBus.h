/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef EVENTBUS_H_
#define EVENTBUS_H_

#include "Arduino.h"
#include "ArdLog.h"

/* To add new event: 1) Insert new enumeration into BusEvent 2) Increase #EVENTS_SIZE 3) Insert new enum into #BUS_LISTENERS */
enum class BusEvent: uint8_t {
    // #### Values are indexed! ####

    /* 12V yamaha trigger is on. */
    YAMAHA_TRIGGER_ON = 0,

    /* 12V yamaha trigger is off. */
    YAMAHA_TRIGGER_OFF = 1,

    /* Button MENU pressed. */
    BTN_MENU = 2,

    /* Button OK pressed. */
    BTN_OK = 3,

    /* Button CANCEL pressed. */
    BTN_CANCEL = 4,

    /* Any pressed. */
    BTN_ANY = 5,

    /* IR command to flip SUB. */
    IR_SUB_CMD = 6,

    /* IR learn mode on for SUB. */
    IR_SUB_LEARN = 7,

    IR_SUB_SHOW_CODES = 8,

    /* Sub switched to Yamaha */
    SUB_TO_YAMAHA = 9,

    /* Sub switched to Cambridge */
    SUB_TO_CAMBRIDGE = 10,

    /* Speakers and sub switched to Yamaha */
    SPK_TO_YAMAHA = 11,

    /* Speakers and sub switched to Cambridge */
    SPK_TO_CAMBRIDGE = 12,

    SYSTEM_STATE_CHANGE = 13,

    /* Number of elements in this enum. */
    COUNT = 14
};

void eb_fire(BusEvent event, ...);

void eb_reg(BusEvent event, void (*func)(va_list));

#endif /* EVENTBUS_H_ */
