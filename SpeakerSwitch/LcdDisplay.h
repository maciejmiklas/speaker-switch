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
  LcdDisplay();

  void setup(); // from Device.h

private:
  static constexpr const char* NAME = "LC";
  void clear(uint8_t row);
  void print(uint8_t col, uint8_t row, uint8_t size, const char *fmt, ...);
  void cleanRight(char *array, short from, short size);
};

#endif  // LCD_DISPLAY_H