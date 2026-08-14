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

void sr_onSpeakerToYamaha(va_list ap) {
  srRef->onSpeakerToYamaha();
}

void sr_onSpeakerToCambridge(va_list ap) {
  srRef->onSpeakerToCambridge();
}

void SpeakerRelay::onSpeakerToYamaha() {
  digitalWrite(SR_RELAY_PIN, LOW); 
}

void SpeakerRelay::onSpeakerToCambridge() {
  digitalWrite(SR_RELAY_PIN, HIGH); 
}

void SpeakerRelay::setup() {
  srRef = this;

  pinMode(SR_RELAY_PIN, OUTPUT);

  eb_reg(BusEvent::SPEAKER_TO_YAMAHA, &sr_onSpeakerToYamaha);
  eb_reg(BusEvent::SPEAKER_TO_CAMBRIDGE, &sr_onSpeakerToCambridge);
}