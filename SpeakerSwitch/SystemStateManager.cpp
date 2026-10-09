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
#include "SystemStateManager.h"

#include "Util.h"

void SystemStateManager::onAnyButtonPress() {
    lastStateChange = util_ms();
}

SystemStateManager::SystemStateManager() : state(SystemState::IDLE), lastStateChange(0) {
}

SystemState SystemStateManager::get() const {
    return state;
}

bool SystemStateManager::isMenuActive() const {
    return state == SystemState::IR_LEARN || state == SystemState::MAIN_MENU;
}

void SystemStateManager::onCycle() {
    if (state != SystemState::IDLE
        && util_ms() > lastStateChange + SM_IDLE_TIMEOUT_MS) {
        LOG_SM(F("%s GO IDLE"), NAME);
        changeState(SystemState::IDLE);
    }
}

void SystemStateManager::changeState(const SystemState state) {
    lastStateChange = util_ms();

    if (this->state != state) {
        this->state = state;
        eb_fire(BusEvent::SYSTEM_STATE_CHANGE, state);
    }
}

void SystemStateManager::setup() {
    EB_REG(BusEvent::BTN_ANY, this, onAnyButtonPress);
}
