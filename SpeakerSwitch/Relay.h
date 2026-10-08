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
#ifndef RELAY_H
#define RELAY_H

#include "Device.h"
#include "ArdLog.h"
#include "EventBus.h"

class Relay : public Device {
public:
    Relay();

    void onSpeakerToYamaha();

    void onSpeakerToCambridge();

    void onSubToYamaha();

    void onSubToCambridge();

    void setup() override; // from Device.h

    void onCycle() override; // from Device.h

    bool isSpeakerToCambridge() const;

    bool isSubToCambridge() const;

private:
    static constexpr const char *NAME = "RE";

    bool speakerToCambridge;
    bool subToCambridge;

    void switchSpkToYamaha();

    void switchSpkToCambridge();

    void switchSubToYamaha();

    void switchSubToCambridge();
};

#endif  // SUB_RELAY_H
