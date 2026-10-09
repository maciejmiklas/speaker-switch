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

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Device.h"
#include "SystemStateManager.h"
#include "LcdDisplay.h"

enum class MenuPos: uint8_t {
    FIRST = 0,

    SPK_TO_CAM = 1,
    SPK_TO_YAM = 2,
    SUB_TO_CAM = 3,
    SUB_TO_YAM = 4,
    IR_LEARN = 5,
    IR_SHOW_CODES = 6,
    LCD_BRIGHTNESS = 7,

    LAST = LCD_BRIGHTNESS
};

class MainMenu : public Device {
public:
    MainMenu(SystemStateManager *sm, LcdDisplay *lcd);

    void onBtnMenu();

    void onBtnOk() const;

    void onBtnCancel() const;

    void onSystemStateChange(SystemState state);

    void setup() override; // from Device.h
    void onCycle() override; // from Device.h

private:
    static constexpr const char *NAME = "MM";
    SystemStateManager *sm;
    LcdDisplay *lcd;
    MenuPos pos;

    void resetMenu();
};


#endif
