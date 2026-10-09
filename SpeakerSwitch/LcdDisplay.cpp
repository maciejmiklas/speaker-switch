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
#include "LcdDisplay.h"

// https://docs.arduino.cc/learn/electronics/lcd-displays/
static LiquidCrystal lcd(LC_LCD_RS, LC_LCD_E, LC_LCD_D4, LC_LCD_D5, LC_LCD_D6, LC_LCD_D7);

LcdDisplay::LcdDisplay() : brightness(BRIGHTNESS_DEFAULT), pwmCounter(0) {
}

void LcdDisplay::printLine(const uint8_t row, const char *fmt) {
    char buf[17]; // 16 chars + null terminator
    snprintf(buf, sizeof(buf), "%-16s", fmt);

    lcd.setCursor(0, row);
    lcd.print(buf);
}

void LcdDisplay::clear(uint8_t row) {
    lcd.setCursor(0, row);
    lcd.print("                ");
    lcd.setCursor(0, row);
}

void LcdDisplay::printAborting() {
    printLine(0, "ABORTING....");
    clear(1);
}

void LcdDisplay::printSaving() {
    printLine(0, "SAVING....");
    clear(1);
}

void LcdDisplay::printClosing() {
    printLine(0, "CLOSING....");
    clear(1);
}

void LcdDisplay::printLines(const char *line1, const char *line2) {
    printLine(0, line1);
    printLine(1, line2);
}

void LcdDisplay::onBrightnessUp() {
    printLine(0, "BRIGHTNESS");
    brightness++;
    if (brightness > BRIGHTNESS_MAX) {
        brightness = BRIGHTNESS_MIN;
    }

    // Build progress bar: filled chars for brightness level, empty for rest
    char bar[17]; // 16 chars + null terminator
    for (uint8_t i = 0; i < 16; i++) {
        bar[i] = (i < brightness) ? '\xFF' : ' '; // 0xFF is full block character
    }
    bar[16] = '\0';
    printLine(1, bar);
}

void LcdDisplay::setup() {
    pinMode(LC_LCD_K, OUTPUT);
    digitalWrite(LC_LCD_K, HIGH);

    lcd.begin(16, 2);
    lcd.noAutoscroll();

    EB_REG(BusEvent::LCD_BRIGHTNESS_UP, this, onBrightnessUp);
}

void LcdDisplay::onCycle() {
    // Software PWM for backlight - called frequently from main loop
    pwmCounter++;
    if (pwmCounter >= BRIGHTNESS_MAX) {
        pwmCounter = BRIGHTNESS_MIN;
    }

    if (pwmCounter < brightness) {
        digitalWrite(LC_LCD_K, HIGH);
    } else {
        digitalWrite(LC_LCD_K, LOW);
    }
}
