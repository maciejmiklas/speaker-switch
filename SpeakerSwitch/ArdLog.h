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
#define LOG_SW_ON true
#if LOG && LOG_SW_ON
    #define LOG_SW(...) log(__VA_ARGS__)
#else
    #define LOG_SW(...) ((void)0)
#endif

/** Enable logger for: EventBus */
#define LOG_EB_ON true
#if LOG && LOG_EB_ON
    #define LOG_EB(...) log(__VA_ARGS__)
#else
    #define LOG_EB(...) ((void)0)
#endif

/** Enable logger for: Buttons */
#define LOG_BT_ON true
#if LOG && LOG_BT_ON
    #define LOG_BT(...) log(__VA_ARGS__)
#else
    #define LOG_BT(...) ((void)0)
#endif

/** Enable logger for: YamahaTrigger */
#define LOG_YT_ON true
#if LOG && LOG_YT_ON
    #define LOG_YT(...) log(__VA_ARGS__)
#else
    #define LOG_YT(...) ((void)0)
#endif

/** Enable logger for: Relay */
#define LOG_RE_ON true
#if LOG && LOG_RE_ON
    #define LOG_RE(...) log(__VA_ARGS__)
#else
    #define LOG_RE(...) ((void)0)
#endif

/** Enable logger for: IrSubReceiver */
#define LOG_IR_ON true
#if LOG && LOG_IR_ON
    #define LOG_IR(...) log(__VA_ARGS__)
#else
    #define LOG_IR(...) ((void)0)
#endif

/** Enable logger for: LcdDisplay */
#define LOG_LC_ON true
#if LOG && LOG_LC_ON
    #define LOG_LC(...) log(__VA_ARGS__)
#else
    #define LOG_LC(...) ((void)0)
#endif

/** Enable logger for: Display */
#define LOG_DS_ON true
#if LOG && LOG_DS_ON
    #define LOG_DS(...) log(__VA_ARGS__)
#else
    #define LOG_DS(...) ((void)0)
#endif

/** Enable logger for: SystemStateManager */
#define LOG_SM_ON true
#if LOG && LOG_SM_ON
    #define LOG_SM(...) log(__VA_ARGS__)
#else
    #define LOG_SM(...) ((void)0)
#endif

/** Enable logger for: MainMenu */
#define LOG_MM_ON true
#if LOG && LOG_MM_ON
    #define LOG_MM(...) log(__VA_ARGS__)
#else
    #define LOG_MM(...) ((void)0)
#endif

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
    char sbuf[AL_SBUF_SIZE] = {0};

    /** Buffer for sprintf-template passed as first argument to log method. */
    char pgbuf[AL_PGBUF_SIZE] = {0};

    uint16_t lastFreeRam = 0;

    inline void resetBuf(char *buf, uint8_t size);

    inline void resetSbuf();

    inline void resetPgbuf();

    inline void copyPGM(const __FlashStringHelper *ifsh);

    inline uint16_t getFreeRAM();
};
#endif /* ARD_LOG_H */
