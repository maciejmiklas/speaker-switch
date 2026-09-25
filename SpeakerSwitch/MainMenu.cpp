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

static void mm_onSystemStateChange(va_list ap) {
    refMen->onSystemStateChange(va_arg(ap, SystemState));
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

void MainMenu::onSystemStateChange(SystemState state) {
    if (state == SystemState::IDLE) {
        resetMenu();
    }
}

void MainMenu::onBtnMenu() {
    LOG_MM(F("%s POS %d"), NAME, static_cast<uint8_t>(pos));

    sm->changeState(SystemState::MAIN_MENU);

    switch (pos) {
        case MenuPos::SPK_TO_CAM:
            lcd->printLine(0, "SPEAKERS TO");
            lcd->printLine(1, "CAMBRIDGE ?");
            break;
        case MenuPos::SPK_TO_YAM:
            lcd->printLine(0, "SPEAKERS TO");
            lcd->printLine(1, "YAMAHA ?");
            break;
        case MenuPos::SPK_TO_IR:
            lcd->printLine(0, "IR");
            lcd->printLine(1, "TODO ....");
            break;
    }

    // Move to next position, wrap to first when reaching end
    if (pos == MenuPos::LAST) {
        pos = MenuPos::FIRST;
    } else {
        pos = static_cast<MenuPos>(static_cast<uint8_t>(pos) + 1);
    }
}

void MainMenu::onBtnOk() {
    if (sm->get() == SystemState::MAIN_MENU) {
        switch (pos) {
            case MenuPos::SPK_TO_CAM:
                lcd->printLine(0, "SPEAKERS TO");
                lcd->printLine(1, "CAMBRIDGE ?");
                break;
            case MenuPos::SPK_TO_YAM:
                lcd->printLine(0, "SPEAKERS TO");
                lcd->printLine(1, "YAMAHA ?");
                break;
        }
    }
}

void MainMenu::resetMenu() {
    pos = MenuPos::FIRST;
}

void MainMenu::setup() {
    eb_reg(BusEvent::BTN_CANCEL, &mm_onBtnCancel);
    eb_reg(BusEvent::BTN_MENU, &mm_onBtnMenu);
    eb_reg(BusEvent::BTN_OK, &mm_onBtnOk);
    eb_reg(BusEvent::SYSTEM_STATE_CHANGE, &mm_onSystemStateChange);
}
