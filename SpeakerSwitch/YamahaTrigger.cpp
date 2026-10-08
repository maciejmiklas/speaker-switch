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
#include "YamahaTrigger.h"

static YamahaTrigger *refAt;

YamahaTrigger::YamahaTrigger() : lastChangeMs(0), currentTriggerLevel(255) {
}

void YamahaTrigger::onCycle() {
    const uint8_t triggerLevel = digitalRead(YT_TRIG_PIN);

    if (triggerLevel == currentTriggerLevel) {
        lastChangeMs = 0;
        return;
    }

    if (lastChangeMs == 0) {
        lastChangeMs = util_ms();
        return;
    }

    if (util_ms() - lastChangeMs < YT_STATE_CHANGE_MS) {
        return;
    }

    currentTriggerLevel = triggerLevel;
    lastChangeMs = 0;

    LOG_YT(F("%s AMP %d"), NAME, triggerLevel);
    sendTriggerEvent(triggerLevel);
    sendSpeakerEvent(triggerLevel);
}

void inline YamahaTrigger::sendTriggerEvent(const uint8_t triggerLevel) {
    if (triggerLevel == HIGH) {
        eb_fire(BusEvent::YAMAHA_TRIGGER_ON);
    } else {
        eb_fire(BusEvent::YAMAHA_TRIGGER_OFF);
    }
}

void inline YamahaTrigger::sendSpeakerEvent(const uint8_t triggerLevel) {
    if (triggerLevel == HIGH) {
        eb_fire(BusEvent::SPK_TO_YAMAHA);
    } else {
        eb_fire(BusEvent::SPK_TO_CAMBRIDGE);
    }
}

void YamahaTrigger::reinitialize() {
    const uint8_t triggerLevel = currentTriggerLevel = digitalRead(YT_TRIG_PIN);
    sendSpeakerEvent(triggerLevel);
}

void YamahaTrigger::setup() {
    pinMode(YT_TRIG_PIN, INPUT);
    refAt = this;
}
