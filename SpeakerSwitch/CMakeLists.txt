cmake_minimum_required(VERSION 3.20)
project(SpeakerSwitch C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_executable(SpeakerSwitch
        ArdLog.cpp
        Buttons.cpp
        Display.cpp
        EventBus.cpp
        IrSubReceiver.cpp
        LcdDisplay.cpp
        Relay.cpp
        Util.cpp
        YamahaTrigger.cpp
)

target_include_directories(SpeakerSwitch PRIVATE
        .
        /Users/mmiklas/Library/Arduino15/packages/arduino/hardware/avr/1.8.8/cores/arduino
        /Users/mmiklas/Library/Arduino15/packages/arduino/hardware/avr/1.8.8/variants/standard
        /Users/mmiklas/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include
)

target_compile_definitions(SpeakerSwitch PRIVATE
        ARDUINO=10819
        ARDUINO_AVR_UNO
        F_CPU=16000000L
)