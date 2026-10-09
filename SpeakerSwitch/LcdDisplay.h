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
#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include "ArdLog.h"
#include "EventBus.h"
#include "Device.h"
#include "Util.h"
#include "LiquidCrystal.h"

class LcdDisplay : public Device {
public:
    static constexpr uint8_t BRIGHTNESS_MIN = 1;
    static constexpr uint8_t BRIGHTNESS_MAX = 16;
    static constexpr uint8_t BRIGHTNESS_DEFAULT = 8;

    LcdDisplay();

    void onBrightnessUp();

    void clear(uint8_t row);

    void printAborting();

    void printClosing();

    void printSaving();

    void printLine(uint8_t row, const char *fmt);

    void printLines(const char *line1,const char *line2);

    void setup() override; // from Device.h

    void onCycle() override; // from Device.h

    uint8_t getBrightness() const { return brightness; }

private:
    static constexpr const char *NAME = "LC";

    uint8_t brightness;
    uint8_t pwmCounter;
};

#endif  // LCD_DISPLAY_H
