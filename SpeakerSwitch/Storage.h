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
#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <EEPROM.h>

class Storage {
public:
    static void saveIrSignals(uint32_t irSignal1, uint32_t irSignal2);
    static bool loadIrSignals(uint32_t &irSignal1, uint32_t &irSignal2);

private:
    static constexpr uint16_t EEPROM_MAGIC_ADDR = 0;
    static constexpr uint32_t EEPROM_MAGIC = 0xDEADBEEF;
    static constexpr uint16_t EEPROM_IR_SIGNAL1_ADDR = 4;
    static constexpr uint16_t EEPROM_IR_SIGNAL2_ADDR = 8;
};

#endif  // STORAGE_H