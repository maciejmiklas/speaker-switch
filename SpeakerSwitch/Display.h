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
#ifndef DISPLAY_H
#define DISPLAY_H

#include "ArdLog.h"
#include "EventBus.h"
#include "Device.h"
#include "Util.h"
#include "LcdDisplay.h"

class Display : public Device {
public:
  Display(LcdDisplay* lcd);

  void onCycle();
  void onSubToYamaha();
  void onSubToCambridge();
  void onSpeakerToYamaha();
  void onSpeakerToCambridge();
  void onYamahaTriggerOn();
  void onYamahaTriggerOff();
  void onRemoteInput();
  void onMenuStart();
  void onMenuEnd();

  // from Device.h
  void setup();

private:
  static constexpr const char* NAME = "DS";
  static constexpr const uint16_t INFO_TRIGGER_OFF = 65000;

  bool speakerToCambridge;
  bool subToCambridge;
  bool autoUpdateEnabled;
  uint16_t infoDisplayMs;
  LcdDisplay* lcd;

  void printSpeakersAssigment();
  void resetInfoDisplay();
  bool autoUpdateOn();
};

#endif  // DISPLAY_H