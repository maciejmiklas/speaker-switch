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

static LiquidCrystal lcd(LC_LCD_RS, LC_LCD_E, LC_LCD_D4, LC_LCD_D5, LC_LCD_D6, LC_LCD_D7);

LcdDisplay* lcdRef;

LcdDisplay::LcdDisplay() {

}

void LcdDisplay::print(uint8_t col, uint8_t row, uint8_t size, const char *fmt, ...) {
  lcd.setCursor(col, row);

	char buf[size + 1];
	va_list va;
	va_start(va, fmt);
	short chars = vsprintf(buf, fmt, va);
	va_end(va);

	cleanRight(buf, chars, size);
	lcd.print(buf);
}

void LcdDisplay::cleanRight(char *array, short from, short size) {
  for (short int i = from; i < size; i++) {
		array[i] = ' ';
	}
	array[size] = '\0';
}

void LcdDisplay::clear(uint8_t row) {
	lcd.setCursor(0, row);
	lcd.print("                ");
	lcd.setCursor(0, row);
}

void lcd_onYamahaTriggerOn(va_list ap) {
  //subRef->onYamahaTriggerOn();
}

// https://docs.arduino.cc/learn/electronics/lcd-displays/
void LcdDisplay::setup() {
  lcdRef = this;

  pinMode(LC_LCD_K, OUTPUT);
  digitalWrite(LC_LCD_K, HIGH); 
  
  lcd.begin(16, 2);
  lcd.noAutoscroll();

  clear(0);
  clear(1);

	lcd.setCursor(0, 0);
	lcd.print("   WELCOME ;)   ");
};