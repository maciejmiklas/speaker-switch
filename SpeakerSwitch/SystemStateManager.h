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

#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include "ArdLog.h"
#include "EventBus.h"
#include "Device.h"

enum class SystemState: uint8_t {
    IDLE = 0,
    MAIN_MENU = 1,
    IR_LEARN = 2
};

class SystemStateManager : public Device {
public:
    SystemStateManager();

    SystemState get() const;

    void onCycle();

    void onAnyButtonPress();

    void changeState(SystemState state);

    // from Device.h
    void setup() override;

private:
    static constexpr const char *NAME = "SM";
    SystemState state;
    uint32_t lastStateChange;
};

#endif
