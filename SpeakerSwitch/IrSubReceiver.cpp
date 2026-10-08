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
#include "IrSubReceiver.h"
#include <IRremote.hpp>

static IrSubReceiver *irRef;

IrSubReceiver::IrSubReceiver(LcdDisplay *lcd,
                             SystemStateManager *ssm) : lcd(lcd),
                                                        ssm(ssm),
                                                        lastChangeMs(0),
                                                        irSignal1(5689),
                                                        irSignal2(7737),
                                                        irLearnSignal1(0),
                                                        irLearnSignal2(0),
                                                        state(IrState::RECEIVING),
                                                        subCambridge(false) {
}

static void ir_onSpeakerToYamaha(va_list ap) {
    irRef->onSpeakerToYamaha();
}

static void ir_onSpeakerToCambridge(va_list ap) {
    irRef->onSpeakerToCambridge();
}

static void ir_onSubToYamaha(va_list ap) {
    irRef->onSubToYamaha();
}

static void ir_onSubToCambridge(va_list ap) {
    irRef->onSubToCambridge();
}

static void ir_learn(va_list ap) {
    irRef->onLearn();
}

static void ir_showCodes(va_list ap) {
    irRef->onShowCodes();
}

static void ir_onBtnOk(va_list ap) {
    irRef->onBtnOk();
}

static void ir_onCancel(va_list ap) {
    irRef->onCancel();
}

void IrSubReceiver::onSpeakerToCambridge() {
    subCambridge = true;
}

void IrSubReceiver::onSpeakerToYamaha() {
    subCambridge = false;
}

void IrSubReceiver::onSubToCambridge() {
    subCambridge = true;
}

void IrSubReceiver::onSubToYamaha() {
    subCambridge = false;
}

void IrSubReceiver::onLearn() {
    if (state != IrState::RECEIVING) {
        return;
    }
    irLearnSignal1 = 0;
    irLearnSignal2 = 0;
    state = IrState::LEARNING;

    lcd->printLine(0, "WAITING.....");
    lcd->printLine(1, "WAITING.....");
}

void IrSubReceiver::learn() {
    uint32_t irin = IrReceiver.decodedIRData.decodedRawData;

    if (irLearnSignal1 == 0) {
        irLearnSignal1 = irin;
        printIrCode(0, irin);
    } else if (irLearnSignal2 == 0 && irin != irLearnSignal1) {
        irLearnSignal2 = irin;
        printIrCode(1, irin);
        delay(SHOW_IR_LEARN2_MS);
    }

    if (irLearnSignal1 != 0 && irLearnSignal2 != 0) {
        lcd->printLine(0, "IR LEARN SUCCESS");
        lcd->printLine(1, "PRESS OK TO SAVE");
        state = IrState::WAITING_FOR_SAVE;
    }
}

void IrSubReceiver::printIrCode(const uint8_t row, const uint32_t signal) const {
    LOG_IR(F("%s S%d:%d"), NAME, row, signal);
    char buf[17];
    snprintf(buf, sizeof(buf), "IR CODE: 0x%lX", (unsigned long) signal);
    lcd->printLine(row, buf);
}

void IrSubReceiver::onCancel() {
    if (state == IrState::SHOW_CODES) {
        exitMenu();
        return;
    }

    if (irLearnSignal1 != 0) {
        irLearnSignal1 = 0;
        irLearnSignal2 = 0;

        lcd->printLine(0, "ABORTING....");
        lcd->clear(1);
    }

    state = IrState::RECEIVING;
    ssm->changeState(SystemState::IDLE);
}

void IrSubReceiver::exitMenu() {
    state = IrState::RECEIVING;
    lcd->printLine(0, "EXITING....");
    lcd->clear(1);
    ssm->changeState(SystemState::IDLE);
}

void IrSubReceiver::onBtnOk() {
    if (state == IrState::SHOW_CODES) {
        exitMenu();
        return;
    }
    if (irLearnSignal1 == 0) {
        return;
    }
    irSignal1 = irLearnSignal1;
    irSignal2 = irLearnSignal2;

    irLearnSignal1 = 0;
    irLearnSignal2 = 0;

    lcd->printLine(0, "SAVING....");
    lcd->clear(1);

    state = IrState::RECEIVING;
    ssm->changeState(SystemState::IDLE);

    Storage::saveIrSignals(irSignal1, irSignal2);
}

void IrSubReceiver::onShowCodes() {
    state = IrState::SHOW_CODES;
    printIrCode(0, irSignal1);
    printIrCode(1, irSignal2);
}

void IrSubReceiver::processIr() {
    if (util_ms() - lastChangeMs < IR_STATE_CHANGE_MS) {
        return;
    }

    lastChangeMs = util_ms();
    uint32_t irin = IrReceiver.decodedIRData.decodedRawData;
    if (irin == irSignal1 || irin == irSignal2) {
        LOG_IR(F("%s CMD:%d"), NAME, irin);

        eb_fire(BusEvent::IR_SUB_CMD);

        subCambridge = !subCambridge;
        eb_fire(subCambridge ? BusEvent::SUB_TO_CAMBRIDGE : BusEvent::SUB_TO_YAMAHA);
    }
}

void IrSubReceiver::onCycle() {
    if (!IrReceiver.decode()) {
        return;
    }

    if (state == IrState::LEARNING) {
        learn();
    } else {
        processIr();
    }

    IrReceiver.resume();
}

void IrSubReceiver::setup() {
    irRef = this;
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    // Load IR signals from EEPROM if valid
    if (Storage::loadIrSignals(irSignal1, irSignal2)) {
        LOG_IR(F("%s Loaded IR codes: 0x%lX, 0x%lX"), NAME, (unsigned long)irSignal1, (unsigned long)irSignal2);
    }

    eb_reg(BusEvent::IR_SUB_LEARN, &ir_learn);
    eb_reg(BusEvent::IR_SUB_SHOW_CODES, &ir_showCodes);
    eb_reg(BusEvent::SPK_TO_YAMAHA, &ir_onSpeakerToYamaha);
    eb_reg(BusEvent::SPK_TO_CAMBRIDGE, &ir_onSpeakerToCambridge);
    eb_reg(BusEvent::SUB_TO_YAMAHA, &ir_onSubToYamaha);
    eb_reg(BusEvent::SUB_TO_CAMBRIDGE, &ir_onSubToCambridge);
    eb_reg(BusEvent::BTN_OK, &ir_onBtnOk);
    eb_reg(BusEvent::BTN_CANCEL, &ir_onCancel);
}
