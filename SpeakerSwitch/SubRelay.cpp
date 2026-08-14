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
#include "SubRelay.h"

SubRelay* subRef;

SubRelay::SubRelay() {

}

void sur_onSubToYamaha(va_list ap) {
  subRef->onSubToYamaha();
}

void sur_onSubToCambridge(va_list ap) {
  subRef->onSubToCambridge();
}

void SubRelay::onSubToYamaha() {
  digitalWrite(SU_RELAY_PIN, LOW); 
}

void SubRelay::onSubToCambridge() {
  digitalWrite(SU_RELAY_PIN, HIGH); 
}

void SubRelay::setup() {
  subRef = this;

  pinMode(SU_RELAY_PIN, OUTPUT);

  eb_reg(BusEvent::SUB_TO_YAMAHA, &sur_onSubToYamaha);
  eb_reg(BusEvent::SUB_TO_CAMBRIDGE, &sur_onSubToCambridge);
}