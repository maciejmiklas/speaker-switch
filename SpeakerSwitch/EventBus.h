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

/* To add new event: 1) Insert new enumaration into BusEvent 2) Increase #EVENTS_SIZE 3) Insert new enum into #BUS_LISTENERS */
enum class BusEvent: uint8_t {

  // #### Values are indexed! ####
  CYCLE = 0,

  /* 12V yamaha trigger is on. */
  YAMAHA_TRIGGER_ON, // 1

  /* 12V yamaha trigger is off. */
  YAMAHA_TRIGGER_OFF, // 2

  /* Button MENU pressed. */
  BTN_MENU, // 3

  /* Button OK pressed. */
  BTN_OK, // 4

  /* Button CANCEL pressed. */
  BTN_CANCEL, // 5

  /* IR command to flip SUB. */
  IR_SUB_CMD, // 6

  /* IR learn mode on for SUB. */
  IR_SUB_LEARN, // 7

  /* IR has learned value 1. */
  IR_SUB_LEARNED_1, // 8

  /* IR has learned value 1. */
  IR_SUB_LEARNED_2, // 9

  /* IR has learned both values */
  IR_SUB_LEARNED_OK, // 10

  IR_SUB_SAVE, // 11

  IR_SUB_CANCEL, // 11

  /* Number of elements in this enum. */
  COUNT
};

void eb_fire(BusEvent event, ...);
void eb_reg(BusEvent event, void (*func)(va_list));

#endif /* EVENTBUS_H_ */
