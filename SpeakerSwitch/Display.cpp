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

static Display *dispRef;

Display::Display(LcdDisplay *lcd, SystemStateManager *ssm) : speakerToCambridge(false), subToCambridge(false),
                                                             infoDisplayMs(INFO_TRIGGER_OFF), lcd(lcd), ssm(ssm) {
}

static void disp_onSystemStateChanged(va_list ap) {
    dispRef->onSystemStateChanged(va_arg(ap, SystemState));
}

static void disp_onRemoteInput(va_list ap) {
    dispRef->onRemoteInput();
}

static void disp_onYamahaTriggerOn(va_list ap) {
    dispRef->onYamahaTriggerOn();
}

static void disp_onYamahaTriggerOff(va_list ap) {
    dispRef->onYamahaTriggerOff();
}

static void disp_onSubToYamaha(va_list ap) {
    dispRef->onSubToYamaha();
}

static void disp_onSubToCambridge(va_list ap) {
    dispRef->onSubToCambridge();
}

static void disp_onCycle(va_list ap) {
    dispRef->onCycle();
}

void Display::onSubToYamaha() {
    subToCambridge = false;
}

void Display::onSubToCambridge() {
    subToCambridge = true;
}

void Display::onYamahaTriggerOn() {
    speakerToCambridge = false;
    subToCambridge = false;
    if (autoRefresh()) {
        lcd->printLine(0, "YAMAHA 12V TRIG.");
        lcd->printLine(1, "       ON");
        resetInfoDisplay();
    }
}

void Display::onYamahaTriggerOff() {
    speakerToCambridge = true;
    subToCambridge = true;
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

bool Display::autoRefresh() const {
    return ssm->get() == SystemState::IDLE;
}

void Display::onSystemStateChanged(SystemState state) {
    if (state == SystemState::IDLE) {
        resetInfoDisplay();
    }
}

void Display::resetInfoDisplay() {
    infoDisplayMs = util_ms() + DS_INFO_DELAY_MS;
}

void Display::printSpeakersAssigment() const {
    // row 0
    if (speakerToCambridge) {
        lcd->printLine(0, "SPK: CAMBRIDGE");
    } else {
        lcd->printLine(0, "SPK: YAMAHA");
    }

    // row 1
    if (subToCambridge) {
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

void Display::setup() {
    dispRef = this;

    eb_reg(BusEvent::SUB_TO_YAMAHA, &disp_onSubToYamaha);
    eb_reg(BusEvent::SUB_TO_CAMBRIDGE, &disp_onSubToCambridge);
    eb_reg(BusEvent::CYCLE, &disp_onCycle);
    eb_reg(BusEvent::SYSTEM_STATE_CHANGE, &disp_onSystemStateChanged);
    eb_reg(BusEvent::YAMAHA_TRIGGER_ON, &disp_onYamahaTriggerOn);
    eb_reg(BusEvent::YAMAHA_TRIGGER_OFF, &disp_onYamahaTriggerOff);
    eb_reg(BusEvent::IR_SUB_CMD, &disp_onRemoteInput);

    lcd->printLine(0, APP_NAME);
    lcd->printLine(1, VERSION);
    resetInfoDisplay();
}
