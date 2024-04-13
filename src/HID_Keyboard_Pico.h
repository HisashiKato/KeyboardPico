/*
  HID_Keyboard_Pico.h

  Modified by HisashiKato

  Modified by Earle F. Philhower, III <earlephilhower@yahoo.com>
  Main Arduino Library Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <Arduino.h>
#include "KeyboardLayout.h"

// Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct {
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t keys[6];
} KeyReport;

class HID_Keyboard_Pico : public Print {
protected:
    KeyReport _keyReport;
    const uint16_t *_asciimap;
    virtual void sendReport(KeyReport* keys) = 0;
    virtual void sendConsumerReport(uint16_t key) = 0;

public:
    HID_Keyboard_Pico(void);
    void begin(const uint16_t *layout = KeyboardLayout_en_US);
    void end(void);
    size_t write(uint8_t c);
    size_t write(const uint8_t *buffer, size_t size);
    size_t press(uint8_t k);
    size_t release(uint8_t k);
    size_t writeID(uint8_t k);
    size_t pressID(uint8_t k);
    size_t releaseID(uint8_t k);
    void releaseAll(void);
    size_t consumerPress(uint16_t k);
    size_t consumerRelease();

    typedef void(*LedCallbackFcn)(bool numlock, bool capslock, bool scrolllock, bool compose, bool kana, void *cbData);
    void onLED(LedCallbackFcn fcn, void *cbData = nullptr);
    LedCallbackFcn _ledCB;
    void * _ledCBdata;
};
