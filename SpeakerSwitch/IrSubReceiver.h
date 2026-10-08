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
#include "LcdDisplay.h"
#include "SystemStateManager.h"
#include "Storage.h"
#include <EEPROM.h>

enum class IrState: uint8_t {
    RECEIVING,
    LEARNING,
    WAITING_FOR_SAVE,
    SHOW_CODES
};

class IrSubReceiver : public Device {
public:
    IrSubReceiver(LcdDisplay *lcd, SystemStateManager *ssm);

    void onLearn();

    void onShowCodes();

    void onBtnOk();

    void onCancel();

    void onSpeakerToYamaha();

    void onSpeakerToCambridge();

    void onSubToYamaha();

    void onSubToCambridge();

    void setup() override; // from Device.h

    void onCycle() override; // from Device.h

private:
    static constexpr const char *NAME = "IR";
    static constexpr uint16_t EEPROM_MAGIC_ADDR = 0;
    static constexpr uint32_t EEPROM_MAGIC = 0xDEADBEEF;
    static constexpr uint16_t EEPROM_IR_SIGNAL1_ADDR = 4;
    static constexpr uint16_t EEPROM_IR_SIGNAL2_ADDR = 8;

    LcdDisplay *lcd;
    SystemStateManager *ssm;
    uint32_t lastChangeMs;
    uint32_t irSignal1;
    uint32_t irSignal2;
    uint32_t irLearnSignal1;
    uint32_t irLearnSignal2;
    IrState state;
    bool subCambridge;

    void learn();

    void processIr();

    void printIrCode(uint8_t row, uint32_t signal) const;

    void exitMenu();
};

#endif  // IR_SUB_RECEIVER_H
