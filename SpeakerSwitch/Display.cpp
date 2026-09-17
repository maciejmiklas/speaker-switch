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

Display::Display(LcdDisplay *lcd) : speakerToCambridge(false), subToCambridge(false), autoUpdateEnabled(true),
                                    infoDisplayMs(INFO_TRIGGER_OFF), lcd(lcd) {
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

static void disp_onMenuStart(va_list ap) {
    dispRef->onMenuStart();
}

static void disp_onMenuEnd(va_list ap) {
    dispRef->onMenuEnd();
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
    if (autoUpdateEnabled) {
        lcd->print(0, 0, 16, "YAMAHA 12V TRIG.");
        lcd->print(1, 0, 16, "       ON       ");
        resetInfoDisplay();
    }
}

void Display::onYamahaTriggerOff() {
    speakerToCambridge = true;
    subToCambridge = true;
    if (autoUpdateEnabled) {
        lcd->print(0, 0, 16, "YAMAHA 12V TRIG.");
        lcd->print(1, 0, 16, "       OFF      ");
        resetInfoDisplay();
    }
}

void Display::onRemoteInput() {
    if (autoUpdateEnabled) {
        lcd->print(0, 0, 16, "REMOTE CONTROL  ");
        lcd->print(1, 0, 16, "SIGNAL RECEIVED ");
        resetInfoDisplay();
    }
}

void Display::onMenuStart() {
    autoUpdateEnabled = false;
}

void Display::onMenuEnd() {
    autoUpdateEnabled = true;
    resetInfoDisplay();
}

void Display::resetInfoDisplay() {
    infoDisplayMs = util_ms() + DS_INFO_DELAY_MS;
}

void Display::printSpeakersAssigment() const {
    // row 0
    lcd->print(0, 0, 16, "SPK: "); // pos: 5
    if (speakerToCambridge) {
        lcd->print(0, 5, 16, "CAMBRIDGE  ");
    } else {
        lcd->print(0, 5, 16, "YAMAHA     ");
    }

    // row 1
    lcd->print(1, 0, 16, "SUB: "); // pos: 5
    if (subToCambridge) {
        lcd->print(1, 5, 16, "CAMBRIDGE  ");
    } else {
        lcd->print(1, 5, 16, "YAMAHA     ");
    }
}

void Display::onCycle() {
    if (autoUpdateEnabled && infoDisplayMs != INFO_TRIGGER_OFF && util_ms() > infoDisplayMs) {
        infoDisplayMs = INFO_TRIGGER_OFF;
        printSpeakersAssigment();
    }
}

void Display::setup() {
    dispRef = this;

    eb_reg(BusEvent::SUB_TO_YAMAHA, &disp_onSubToYamaha);
    eb_reg(BusEvent::SUB_TO_CAMBRIDGE, &disp_onSubToCambridge);
    eb_reg(BusEvent::CYCLE, &disp_onCycle);
    eb_reg(BusEvent::MENU_START, &disp_onMenuStart);
    eb_reg(BusEvent::MENU_END, &disp_onMenuEnd);
    eb_reg(BusEvent::YAMAHA_TRIGGER_ON, &disp_onYamahaTriggerOn);
    eb_reg(BusEvent::YAMAHA_TRIGGER_OFF, &disp_onYamahaTriggerOff);
    eb_reg(BusEvent::IR_SUB_CMD, &disp_onRemoteInput);

    lcd->print(0, 0, 16, APP_NAME);
    lcd->print(1, 0, 16, VERSION);
    resetInfoDisplay();
}
