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
#ifndef IR_SUB_RECEIVER_H
#define IR_SUB_RECEIVER_H

#include "ArdLog.h"
#include "EventBus.h"
#include "Device.h"
#include "Util.h"

class IrSubReceiver : public Device {
public:
  IrSubReceiver();

  void onCycle();

  // from Device.h
  void setup();

  void onLearn();

private:
  static constexpr const char* NAME = "IT";
  uint32_t lastChangeMs;
  uint32_t irSignal1;
  uint32_t irSignal2;
  uint32_t irLernSignal1;
  uint32_t irLernSignal2;
  bool lerning;
  void learn();
  void processIr();
};

#endif  // IR_SUB_RECEIVER_H