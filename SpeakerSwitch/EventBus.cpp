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
#include "EventBus.h"

static constexpr const char *NAME = "EB";

static constexpr uint8_t EVENTS_SIZE = static_cast<uint8_t>(BusEvent::COUNT);

/** Max listeners pro event, not a total amount of the listeners. */
static constexpr uint8_t EVENT_LISTENERS_MAX = 6;

static void (*BUS_LIST_FN[EVENTS_SIZE][EVENT_LISTENERS_MAX])(va_list);

static uint8_t BUS_LIST_FN_SIZE[EVENTS_SIZE] = {0};

static uint8_t eb_getFnIdx(BusEvent event) {
    return static_cast<int>(event);
}

void eb_reg(BusEvent event, void ((*fn)(va_list))) {
    const uint8_t eventIdx = eb_getFnIdx(event);
    const uint8_t fnIdx = BUS_LIST_FN_SIZE[eventIdx]++;
    if (fnIdx >= EVENT_LISTENERS_MAX) {
        LOG_EB(F("%s LN OVERFLOW"), NAME);
        BUS_LIST_FN_SIZE[eventIdx]--;
        return;
    }
    BUS_LIST_FN[eventIdx][fnIdx] = fn;
    LOG_EB(F("%s REG %d=%d"), NAME, static_cast<int>(event), fnIdx);
}

void eb_fire(const BusEvent event, ...) {
    va_list ap;
    va_start(ap, event);

    const uint8_t eventIdx = eb_getFnIdx(event);
    const uint8_t eventsSize = BUS_LIST_FN_SIZE[eventIdx];

    if (event != BusEvent::CYCLE) {
        log(F("%s EVENT %d->%d"), NAME, eventIdx, eventsSize);
    }

    for (uint8_t fnIdx = 0; fnIdx < eventsSize; fnIdx++) {
        BUS_LIST_FN[eventIdx][fnIdx](ap);
    }
    va_end(ap);
}
