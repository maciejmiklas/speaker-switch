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
#include "ArdLog.h"
#include "Util.h"
#include "EventBus.h"
#include "Buttons.h"
#include "YamahaTrigger.h"
#include "Relay.h"
#include "IrSubReceiver.h"
#include "LcdDisplay.h"
#include "Display.h"
#include "MainMenu.h"
#include "SystemStateManager.h"

static SystemStateManager *ssm = new SystemStateManager();
static Buttons *btn = new Buttons();
static Relay *re = new Relay();
static LcdDisplay *lcd = new LcdDisplay();
static IrSubReceiver *irs = new IrSubReceiver(lcd, ssm);
static YamahaTrigger *yt = new YamahaTrigger();
static Display *disp = new Display(lcd, ssm, re);
static MainMenu *mm = new MainMenu(ssm, lcd);

static constexpr uint8_t DEVICES = 8;
static Device *dev[DEVICES] = {btn, re, irs, lcd, yt, disp, ssm, mm};

void setup() {
#if LOG
    log_setup();
#endif

    LOG_SW(F("\n\n### SETUP ###"));

    util_cycle();

    for (uint8_t i = 0; i < DEVICES; i++) {
        dev[i]->setup();
    }

    yt->reinitialize();
}

void loop() {
    // LOG_SW(F("\n\n### LOOP ###"));
    util_cycle();

    for (uint8_t i = 0; i < DEVICES; i++) {
        dev[i]->onCycle();
    }
}

