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

static const uint8_t EVENTS_SIZE = 7;

/* To add new event: 1) Insert new enumaration into BusEvent 2) Increase #EVENTS_SIZE 3) Insert new enum into #BUS_LISTENERS */
enum class BusEvent {

  /* 12V amp trigger is on. */
  AMP_TRIGGER_ON = 10,

  /* 12V amp trigger is off. */
  AMP_TRIGGER_OFF = 11,

  /* Button MENU pressed. */
  BTN_MENU = 20,

  /* Button OK pressed. */
  BTN_OK = 21,

  /* Button CANCEL pressed. */
  BTN_CANCEL = 22,

  /* IR lern mode on for SUB. */
  LERN_SUB_IR = 100,

  CYCLE = 255
};

void eb_fire(BusEvent event, ...);
void eb_reg(BusEvent event, void (*func)(va_list));

#endif /* EVENTBUS_H_ */
