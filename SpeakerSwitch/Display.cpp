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
#include "Display.h"

Display::Display(
    LcdDisplay *lcd,
    SystemStateManager *ssm,
    Relay *relay) : infoDisplayMs(INFO_TRIGGER_OFF),
                    lcd(lcd),
                    ssm(ssm), relay(relay) {
}

void Display::onYamahaTriggerOn() {
    if (autoRefresh()) {
        lcd->printLine(0, "YAMAHA 12V TRIG.");
        lcd->printLine(1, "       ON");
        resetInfoDisplay();
    }
}

void Display::onYamahaTriggerOff() {
    if (autoRefresh()) {
        lcd->printLine(0, "YAMAHA 12V TRIG.");
        lcd->printLine(1, "       OFF");
        resetInfoDisplay();
    }
}

void Display::onRemoteInput() {
    if (autoRefresh()) {
        lcd->printLine(0, "REMOTE CONTROL");
        lcd->printLine(1, "SIGNAL RECEIVED");
        resetInfoDisplay();
    }
}

void Display::onSystemStateChanged(const SystemState state) {
    if (state == SystemState::IDLE){
        resetInfoDisplay();
    }
}

void Display::resetInfoDisplay() {
    infoDisplayMs = util_ms() + DS_INFO_DELAY_MS;
}

void Display::printSpeakersAssigment() const {
    // row 0
    if (relay->isSpeakerToCambridge()) {
        lcd->printLine(0, "SPK: CAMBRIDGE");
    } else {
        lcd->printLine(0, "SPK: YAMAHA");
    }

    // row 1
    if (relay->isSubToCambridge()) {
        lcd->printLine(1, "SUB: CAMBRIDGE");
    } else {
        lcd->printLine(1, "SUB: YAMAHA");
    }
}

void Display::onCycle() {
    if (autoRefresh() && infoDisplayMs != INFO_TRIGGER_OFF && util_ms() > infoDisplayMs) {
        infoDisplayMs = INFO_TRIGGER_OFF;
        printSpeakersAssigment();
    }
}

bool Display::autoRefresh() const {
    return ssm->get() == SystemState::IDLE;
}

void Display::setup() {
    EB_REG_ARG(BusEvent::SYSTEM_STATE_CHANGE, this, onSystemStateChanged,SystemState);
    EB_REG(BusEvent::YAMAHA_TRIGGER_ON, this, onYamahaTriggerOn);
    EB_REG(BusEvent::YAMAHA_TRIGGER_OFF, this, onYamahaTriggerOff);
    EB_REG(BusEvent::IR_SUB_CMD, this, onRemoteInput);

    lcd->printLine(0, APP_NAME);
    lcd->printLine(1, VERSION);
    resetInfoDisplay();
}
