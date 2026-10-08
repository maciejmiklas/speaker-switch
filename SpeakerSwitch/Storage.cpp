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
#include "Storage.h"

void Storage::saveIrSignals(uint32_t irSignal1, uint32_t irSignal2) {
    uint32_t magic = EEPROM_MAGIC;
    EEPROM.put(EEPROM_MAGIC_ADDR, magic);
    EEPROM.put(EEPROM_IR_SIGNAL1_ADDR, irSignal1);
    EEPROM.put(EEPROM_IR_SIGNAL2_ADDR, irSignal2);
}

bool Storage::loadIrSignals(uint32_t &irSignal1, uint32_t &irSignal2) {
    uint32_t magic;
    EEPROM.get(EEPROM_MAGIC_ADDR, magic);
    if (magic == EEPROM_MAGIC) {
        EEPROM.get(EEPROM_IR_SIGNAL1_ADDR, irSignal1);
        EEPROM.get(EEPROM_IR_SIGNAL2_ADDR, irSignal2);
        return true;
    }
    return false;
}