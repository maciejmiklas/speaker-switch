/*
   Licensed to the Apache Software Foundation (ASF) under one or more
   contributor license agreements.  See the NOTICE file distributed with
   this work for additional information regarding copyright ownership.
   The ASF licenses this file to You under the Apache License, Version 2.0
   (the "License"); you may not use this file except in compliance with
   the License.  You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#ifndef ARD_LOG_H
#define ARD_LOG_H

#include "Config.h"
#include <stdarg.h>

/** Enables logger so that it can log over serial port. */
#define LOG true

/** Enable logger for: SpeakerSwitch */
#define LOG_SW false

/** Enable logger for: EventBus */
#define LOG_EB true

/** Enable logger for: Buttons */
#define LOG_BT true

/** Enable logger for: YamahaTrigger */
#define LOG_YT true

/** Enable logger for: SpeakerRelay */
#define LOG_SR true

/** Enable logger for: SubRelay */
#define LOG_SU true

/** Enable logger for: IrReceiver */
#define LOG_IR true

void log_setup();
void log_cycle();
void log(const __FlashStringHelper *ifsh, ...);

class Logger {
public:
  Logger();
  void setup();
  void logv(const __FlashStringHelper *ifsh, va_list args);
  void log(const __FlashStringHelper *ifsh, ...);
  void logRAM(char const *msg);
  void logChangeRAM();

private:

  /** Buffer for created message */
  char sbuf[AL_SBUF_SIZE] = { 0 };

  /** Buffer for sprintf-template passed as first argument to log method. */
  char pgbuf[AL_PGBUF_SIZE] = { 0 };

  uint16_t lastFreeRam = 0;

  inline void resetBuf(char *buf, uint8_t size);
  inline void resetSbuf();
  inline void resetPgbuf();
  inline void copyPGM(const __FlashStringHelper *ifsh);

  inline uint16_t getFreeRAM();
};
#endif /* ARD_LOG_H */
