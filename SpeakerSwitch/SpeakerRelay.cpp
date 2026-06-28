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
#include "SpeakerRelay.h"

SpeakerRelay* srRef;

SpeakerRelay::SpeakerRelay() {

}

void sr_onYamahaTriggerOn(va_list ap) {
  srRef->onYamahaTriggerOn();
}

void sr_onYamahaTriggerOff(va_list ap) {
  srRef->onYamahaTriggerOff();
}

void SpeakerRelay::onYamahaTriggerOn() {
  #if LOG && LOG_SR
      log(F("%s YAM SPK ON"), NAME);
  #endif
  digitalWrite(SR_RELAY_PIN, HIGH); 
}

void SpeakerRelay::onYamahaTriggerOff() {
  #if LOG && LOG_SR
      log(F("SR YAM SPK OFF"));
  #endif
  digitalWrite(SR_RELAY_PIN, LOW); 
}

void SpeakerRelay::setup() {
  srRef = this;

  pinMode(SR_RELAY_PIN, OUTPUT);
  digitalWrite(SR_RELAY_PIN, LOW); 

  eb_reg(BusEvent::YAMAHA_TRIGGER_ON, &sr_onYamahaTriggerOn);
  eb_reg(BusEvent::YAMAHA_TRIGGER_OFF, &sr_onYamahaTriggerOff);
}