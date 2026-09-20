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

#include "MainMenu.h"

static MainMenu *refMen;

static void mm_onBtnCancel(va_list ap) {
    refMen->onBtnCancel();
}

static void mm_onBtnMenu(va_list ap) {
    refMen->onBtnMenu();
}

static void mm_onBtnOk(va_list ap) {
    refMen->onBtnOk();
}

MainMenu::MainMenu(SystemStateManager *sm, LcdDisplay *lcd) : sm(sm), lcd(lcd), pos(MenuPos::SPK_TO_CAM) {
    refMen = this;
}

void MainMenu::onBtnCancel() {
}

void MainMenu::onBtnMenu() {
    if (sm->get() != SystemState::IDLE) {
        return;
    }

    // Move to next position, wrap to first when reaching end
    if (pos == MenuPos::SPK_TO_IR) {
        pos = MenuPos::SPK_TO_CAM;
    } else {
        pos = static_cast<MenuPos>(static_cast<uint8_t>(pos) + 1);
    }

    switch (pos) {
        case MenuPos::SPK_TO_CAM:
            lcd->printLine(0, "SPK TO");
            lcd->printLine(0, "CAMBRIDGE ?");
            break;
        case MenuPos::SPK_TO_YAM:
            lcd->printLine(0, "SPK TO ");
            lcd->printLine(0, "YAMAHA ?");
            break;
        case MenuPos::SPK_TO_IR:
            break;
    }
}

void MainMenu::onBtnOk() {
}

void MainMenu::setup() {
    eb_reg(BusEvent::BTN_CANCEL, &mm_onBtnCancel);
    eb_reg(BusEvent::BTN_MENU, &mm_onBtnMenu);
    eb_reg(BusEvent::BTN_OK, &mm_onBtnOk);
}
