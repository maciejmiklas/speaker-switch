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

Relay::Relay() : speakerToCambridge(false), subToCambridge(false) {
}

void Relay::onSpeakerToYamaha() {
    LOG_RE(F("%s SPK TO YAMAHA"), NAME);
    switchSpkToYamaha();
    switchSubToYamaha();
}

void Relay::onSpeakerToCambridge() {
    LOG_RE(F("%s SPK TO CAMBRIDGE"), NAME);
    switchSpkToCambridge();
    switchSubToCambridge();
}

void Relay::onSubToYamaha() {
    LOG_RE(F("%s SUB TO YAMAHA"), NAME);
    switchSubToYamaha();
}

void Relay::onSubToCambridge() {
    LOG_RE(F("%s SUB TO CAMBRIDGE"), NAME);
    switchSubToCambridge();
}

inline void Relay::switchSpkToYamaha() {
    digitalWrite(RE_SPK_PIN, LOW);
    speakerToCambridge = false;
}

inline void Relay::switchSpkToCambridge() {
    digitalWrite(RE_SPK_PIN, HIGH);
    speakerToCambridge = true;
}

inline void Relay::switchSubToYamaha() {
    digitalWrite(RE_SUB_PIN, LOW);
    subToCambridge = false;
}

inline void Relay::switchSubToCambridge() {
    digitalWrite(RE_SUB_PIN, HIGH);
    subToCambridge = true;
}

void Relay::setup() {

    pinMode(RE_SUB_PIN, OUTPUT);
    pinMode(RE_SPK_PIN, OUTPUT);

    EB_REG(BusEvent::SPK_TO_YAMAHA, this, onSpeakerToYamaha);
    EB_REG(BusEvent::SPK_TO_CAMBRIDGE, this, onSpeakerToCambridge);
    EB_REG(BusEvent::SUB_TO_YAMAHA, this, onSubToYamaha);
    EB_REG(BusEvent::SUB_TO_CAMBRIDGE, this, onSubToCambridge);
}

void Relay::onCycle() {
}

bool Relay::isSpeakerToCambridge() const {
    return speakerToCambridge;
}

bool Relay::isSubToCambridge() const {
    return subToCambridge;
}
