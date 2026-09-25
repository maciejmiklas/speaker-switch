/*
   Licensed to the Apache Software Foundation (ASF) under one or more
   contributor license agreements.  See the NOTICE file distributed with
   this work for additional information regarding copyright ownership.
   The ASF licenses this file to You under the Apache License, Version 2.0
   (the "License"); you may not use this file except in compliance with
   the License.  You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "Buttons.h"

static Buttons *refButtons;

static void buttons_onCycle(va_list ap) {
    refButtons->onCycle();
}

Buttons::Buttons()
    : processMs(0), repeatMs(0), lastButton(0) {
}

void Buttons::setup() {
    setupButton(BT_PIN_MENU);
    setupButton(BT_PIN_OK);
    setupButton(BT_PIN_CANCEL);

    refButtons = this;
    eb_reg(BusEvent::CYCLE, &buttons_onCycle);
}

void Buttons::onCycle() {
    if (util_ms() - processMs < BT_PRESS_MS) {
        return;
    }
    readButtons();
    processMs = util_ms();
}

bool Buttons::canProcess(const uint8_t pin) {
    if (digitalRead(pin) != LOW) {
        return false;
    }

    if (lastButton == pin) {
        if (util_ms() - repeatMs < BT_REP_PRESS_MS) {
            return false;
        }
        repeatMs = util_ms();
    } else {
        lastButton = pin;
        repeatMs = util_ms();
    }
    return true;
}

void Buttons::readButtons() {

    if (canProcess(BT_PIN_MENU)) {
        LOG_BT(F("%s MENU"), NAME);
        eb_fire(BusEvent::BTN_MENU);
        eb_fire(BusEvent::BTN_ANY);

    } else if (canProcess(BT_PIN_OK)) {
        LOG_BT(F("%s OK"), NAME);
        eb_fire(BusEvent::BTN_OK);
        eb_fire(BusEvent::BTN_ANY);

    } else if (canProcess(BT_PIN_CANCEL)) {
        LOG_BT(F("%s CANCEL"), NAME);
        eb_fire(BusEvent::BTN_CANCEL);
        eb_fire(BusEvent::BTN_ANY);
    }
}

void Buttons::setupButton(uint8_t pin) {
    pinMode(pin, INPUT);
    pinMode(pin, INPUT_PULLUP);
}
