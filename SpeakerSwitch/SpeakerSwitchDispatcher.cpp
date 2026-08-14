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
#include "SpeakerSwitchDispatcher.h"


SpeakerSwitchDispatcher* ssdRef;

SpeakerSwitchDispatcher::SpeakerSwitchDispatcher(): subCambridge(true) {

}

void sd_onYamahaTriggerOn(va_list ap) {
  ssdRef->onYamahaTriggerOn();
}

void sd_onYamahaTriggerOff(va_list ap) {
  ssdRef->onYamahaTriggerOff();
}

void sd_onSubCmd(va_list ap) {
  ssdRef->onSubCmd();
}

void SpeakerSwitchDispatcher::onYamahaTriggerOn() {
  subCambridge = false;

  #if LOG && LOG_SD
    log(F("%s YAM ON"), NAME);
  #endif
  eb_fire(BusEvent::SPEAKER_TO_YAMAHA);
  eb_fire(BusEvent::SUB_TO_YAMAHA);
}

void SpeakerSwitchDispatcher::onYamahaTriggerOff() {
  subCambridge = true;

  #if LOG && LOG_SD
    log(F("%s CAMB ON"), NAME);
  #endif
  eb_fire(BusEvent::SPEAKER_TO_CAMBRIDGE);
  eb_fire(BusEvent::SUB_TO_CAMBRIDGE);
}

void SpeakerSwitchDispatcher::onSubCmd() {
  subCambridge = !subCambridge;
  if(subCambridge) {
    #if LOG && LOG_SD
      log(F("%s SUB YAM"), NAME);
    #endif
    eb_fire(BusEvent::SUB_TO_CAMBRIDGE);
  } else {
    #if LOG && LOG_SD
      log(F("%s SUB CAMB"), NAME);
    #endif
    eb_fire(BusEvent::SUB_TO_YAMAHA);
  }
}

void SpeakerSwitchDispatcher::setup() {
  ssdRef = this;

  eb_reg(BusEvent::YAMAHA_TRIGGER_ON, &sd_onYamahaTriggerOn);
  eb_reg(BusEvent::YAMAHA_TRIGGER_OFF, &sd_onYamahaTriggerOff);
  eb_reg(BusEvent::IR_SUB_CMD, &sd_onSubCmd);
}
