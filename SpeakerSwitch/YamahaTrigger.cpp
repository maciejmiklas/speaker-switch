#include "Arduino.h"
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
#include "YamahaTrigger.h"

YamahaTrigger* refAt;

YamahaTrigger::YamahaTrigger(): currentTriggerLevel(LOW), lastChangeMs(0) {

}

void at_onCycle(va_list ap) {
  refAt->onCycle();
}

void YamahaTrigger::onCycle() {
  uint8_t triggerLevel = digitalRead(YT_TRIG_PIN);

  if(triggerLevel == currentTriggerLevel) {
    lastChangeMs = 0;
    return;
  }

  if(lastChangeMs == 0) {
    lastChangeMs = util_ms();
    return;
  }

  if(util_ms() - lastChangeMs < YT_STATE_CHANGE_MS) {
    return;
  }

  currentTriggerLevel = triggerLevel;
  lastChangeMs = 0;

  #if LOG && LOG_AT
    log(F("%s AMP %d"), NAME, triggerLevel);
  #endif
  eb_fire(triggerLevel == HIGH ? BusEvent::YAMAHA_TRIGGER_ON:BusEvent::YAMAHA_TRIGGER_OFF);
}

void YamahaTrigger::setup() {
  pinMode(YT_TRIG_PIN, INPUT);
  refAt = this;
  eb_reg(BusEvent::CYCLE, &at_onCycle);
}