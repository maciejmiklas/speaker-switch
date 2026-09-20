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

IrSubReceiver::IrSubReceiver() : lastChangeMs(0), irSignal1(5689), irSignal2(7737), irLearnSignal1(0),
                                 irLearnSignal2(0), learning(false) {
}

static void ir_learn(va_list ap) {
    irRef->onLearn();
}

static void ir_onCycle(va_list ap) {
    irRef->onCycle();
}

static void ir_onSave(va_list ap) {
    irRef->onSave();
}

static void ir_onCancel(va_list ap) {
    irRef->onCancel();
}

void IrSubReceiver::onLearn() {
    irLearnSignal1 = 0;
    irLearnSignal2 = 0;
    learning = true;
}

void IrSubReceiver::learn() {
    uint32_t irin = IrReceiver.decodedIRData.decodedRawData;

    if (irLearnSignal1 == 0) {
        irLearnSignal1 = irin;
#if LOG && LOG_IR
        log(F("%s S1:%d"), NAME, irin);
#endif
    } else if (irLearnSignal2 == 0 && irin != irLearnSignal1) {
        irLearnSignal2 = irin;
#if LOG && LOG_IR
        log(F("%s S2:%d"), NAME, irin);
#endif
    }

    if (irLearnSignal1 != 0 && irLearnSignal2 != 0) {
        learning = false;
    }
}

void IrSubReceiver::onCancel() {
    irLearnSignal1 = 0;
    irLearnSignal2 = 0;
    learning = false;
}

void IrSubReceiver::onSave() {
    irSignal1 = irLearnSignal1;
    irSignal2 = irLearnSignal2;

    irLearnSignal1 = 0;
    irLearnSignal2 = 0;
    learning = false;
}

void IrSubReceiver::processIr() {
    if (util_ms() - lastChangeMs < IR_STATE_CHANGE_MS) {
        return;
    }

    lastChangeMs = util_ms();
    uint32_t irin = IrReceiver.decodedIRData.decodedRawData;
    if (irin == irSignal1 || irin == irSignal2) {
#if LOG && LOG_IR
        log(F("%s CMD:%d"), NAME, irin);
#endif
        eb_fire(BusEvent::IR_SUB_CMD);
    }
}

void IrSubReceiver::onCycle() {
    if (!IrReceiver.decode()) {
        return;
    }

    if (learning) {
        learn();
    } else {
        processIr();
    }

    IrReceiver.resume();
}

void IrSubReceiver::setup() {
    irRef = this;
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    eb_reg(BusEvent::CYCLE, &ir_onCycle);
    eb_reg(BusEvent::IR_SUB_LEARN, &ir_learn);
}
