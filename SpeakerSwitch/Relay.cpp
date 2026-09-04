#include "Arduino.h"
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
#include "Relay.h"

Relay* relayRef;

Relay::Relay(): subCambridge(true) {

}

void re_onYamahaTriggerOn(va_list ap) {
  relayRef->onYamahaTriggerOn();
}

void re_onYamahaTriggerOff(va_list ap) {
  relayRef->onYamahaTriggerOff();
}

void re_onSubCmd(va_list ap) {
  relayRef->onSubCmd();
}

void Relay::onYamahaTriggerOn() {
  subCambridge = false;

  #if LOG && LOG_RE
    log(F("%s YAM ON"), NAME);
  #endif
  eb_fire(BusEvent::ALL_SPK_TO_YAMAHA);
  spkToYamaha();
  subToYamaha();
}

void Relay::onYamahaTriggerOff() {
  subCambridge = true;

  #if LOG && LOG_RE
    log(F("%s CAMB ON"), NAME);
  #endif
  eb_fire(BusEvent::ALL_SPK_TO_CAMBRIDGE);
  spkToCambridge();
  subToCambridge();
}

void Relay::onSubCmd() {
  subCambridge = !subCambridge;
  if(subCambridge) {
    #if LOG && LOG_RE
      log(F("%s SUB YAM"), NAME);
    #endif
    eb_fire(BusEvent::SUB_TO_CAMBRIDGE);
    subToYamaha();
  } else {
    #if LOG && LOG_RE
      log(F("%s SUB CAMB"), NAME);
    #endif
    eb_fire(BusEvent::SUB_TO_YAMAHA);
    subToCambridge();
  }
}

inline void Relay::spkToYamaha() {
  digitalWrite(RE_SPK_PIN, LOW); 
}

inline void Relay::spkToCambridge() {
  digitalWrite(RE_SPK_PIN, HIGH); 
}

inline void Relay::subToYamaha() {
  digitalWrite(RE_SUB_PIN, LOW);
}

inline void Relay::subToCambridge() {
  digitalWrite(RE_SUB_PIN, HIGH); 
}

void Relay::setup() {
  relayRef = this;

  pinMode(RE_SUB_PIN, OUTPUT);
  pinMode(RE_SPK_PIN, OUTPUT);

  eb_reg(BusEvent::YAMAHA_TRIGGER_ON, &re_onYamahaTriggerOn);
  eb_reg(BusEvent::YAMAHA_TRIGGER_OFF, &re_onYamahaTriggerOff);
  eb_reg(BusEvent::IR_SUB_CMD, &re_onSubCmd);
}