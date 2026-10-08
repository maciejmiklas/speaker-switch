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

static void mm_onSystemStateChange(va_list ap) {
    refMen->onSystemStateChange(va_arg(ap, SystemState));
}

static void mm_onBtnMenu(va_list ap) {
    refMen->onBtnMenu();
}

static void mm_onBtnOk(va_list ap) {
    refMen->onBtnOk();
}

MainMenu::MainMenu(SystemStateManager *sm, LcdDisplay *lcd) : sm(sm), lcd(lcd), pos(MenuPos::FIRST) {
    refMen = this;
}

void MainMenu::onSystemStateChange(const SystemState state) {
    if (state == SystemState::IDLE) {
        resetMenu();
    }
}

void MainMenu::onBtnMenu() {
    LOG_MM(F("%s POS %d"), NAME, static_cast<uint8_t>(pos));

    sm->changeState(SystemState::MAIN_MENU);

    // Move to next position, wrap to first when reaching end
    if (pos == MenuPos::LAST) {
        pos = MenuPos::FIRST;
    }
    pos = static_cast<MenuPos>(static_cast<uint8_t>(pos) + 1);

    switch (pos) {
        case MenuPos::FIRST:
            break;

        case MenuPos::SPK_TO_CAM:
            lcd->printLines("SPEAKERS TO", "CAMBRIDGE ?");
            break;

        case MenuPos::SPK_TO_YAM:
            lcd->printLines("SPEAKERS TO", "YAMAHA ?");
            break;

        case MenuPos::SUB_TO_CAM:
            lcd->printLines("SUB TO", "CAMBRIDGE ?");
            break;

        case MenuPos::SUB_TO_YAM:
            lcd->printLines("SUB TO", "YAMAHA ?");
            break;

        case MenuPos::IR_LEARN:
            lcd->printLines("LEARN IR CODE", "FOR SUB SWITCH");
            break;

        case MenuPos::IR_SHOW_CODES:
            lcd->printLines("SHOW IR CODES", "FOR SUB SWITCH");
            break;
    }
}

void MainMenu::onBtnOk() const {
    if (!sm->isMenuActive()) {
        return;
    }

    switch (pos) {
        case MenuPos::FIRST:
            break;

        case MenuPos::SPK_TO_CAM:
            lcd->printLines("SWITCHING SPK TO", "CAMBRIDGE");
            eb_fire(BusEvent::SPK_TO_CAMBRIDGE);
            sm->changeState(SystemState::IDLE);
            break;

        case MenuPos::SPK_TO_YAM:
            lcd->printLines("SWITCHING SPK TO", "YAMAHA");
            eb_fire(BusEvent::SPK_TO_YAMAHA);
            sm->changeState(SystemState::IDLE);
            break;

        case MenuPos::SUB_TO_CAM:
            lcd->printLines("SWITCHING SUB TO", "CAMBRIDGE");
            eb_fire(BusEvent::SUB_TO_CAMBRIDGE);
            sm->changeState(SystemState::IDLE);
            break;

        case MenuPos::SUB_TO_YAM:
            lcd->printLines("SWITCHING SUB TO", "YAMAHA");
            eb_fire(BusEvent::SUB_TO_YAMAHA);
            sm->changeState(SystemState::IDLE);
            break;

        case MenuPos::IR_LEARN:
            eb_fire(BusEvent::IR_SUB_LEARN);
            break;

        case MenuPos::IR_SHOW_CODES:
            eb_fire(BusEvent::IR_SUB_SHOW_CODES);
            break;
    }
}

void MainMenu::resetMenu() {
    pos = MenuPos::FIRST;
}

void MainMenu::onCycle() {
}

void MainMenu::setup() {
    eb_reg(BusEvent::BTN_MENU, &mm_onBtnMenu);
    eb_reg(BusEvent::BTN_OK, &mm_onBtnOk);
    eb_reg(BusEvent::SYSTEM_STATE_CHANGE, &mm_onSystemStateChange);
}
