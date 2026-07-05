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
#include "ArdLog.h"
#include "Util.h"
#include "EventBus.h"
#include "Buttons.h"
#include "YamahaTrigger.h"
#include "SpeakerRelay.h"
#include "SubRelay.h"
#include "IrSubReceiver.h"
#include "LcdDisplay.h"


Buttons* btn = new Buttons();
YamahaTrigger* yt = new YamahaTrigger();
SpeakerRelay* sr = new SpeakerRelay();
SubRelay* sub = new SubRelay();
IrSubReceiver* irs = new IrSubReceiver();
LcdDisplay* lcd = new LcdDisplay();

const static uint8_t DEVICES = 6;
Device* dev[DEVICES] = { btn, yt, sr, sub, irs, lcd };

void setup() {

  #if LOG
    log_setup();
  #endif

  #if LOG && LOG_SW
    log(F("\n\n### SETUP ###"));
  #endif

  util_cycle();
  execSetup();
}

void loop() {
  #if LOG && LOG_SW
    log(F("### LOOP ###"));
  #endif

  util_cycle();
  eb_fire(BusEvent::CYCLE);
}

void execSetup() {
  for (uint8_t i = 0; i < DEVICES; i++) {
    dev[i]->setup();
  }
}
