/*
  HID_Keyboard_Pico.cpp

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

#include "KeyboardPico.h"
#include <RP2040USB.h>

#include "tusb.h"
#include "class/hid/hid_device.h"

//================================================================================
//================================================================================
//  Keyboard

HID_Keyboard_Pico::HID_Keyboard_Pico(void) {
    bzero(&_keyReport, sizeof(_keyReport));
    _asciimap = KeyboardLayout_en_US;
    _ledCB = nullptr;
}

void HID_Keyboard_Pico::begin(const uint16_t *layout) {
    _asciimap = layout;
}

void HID_Keyboard_Pico::end(void) {
}

// press() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way
// USB HID works, the host acts like the key remains pressed until we
// call release(), releaseAll(), or otherwise clear the report and resend.
size_t HID_Keyboard_Pico::press(uint8_t k)
{
    uint8_t i;
    uint16_t key;

    if (k > 0xE7) {
        setWriteError();
        return 0;
    } else if (k >= 0xE0) { // it's a modifier key
        _keyReport.modifiers |= (1<<(k-0xE0));
        key = 0;
    } else {                // it's a printing key
        key = pgm_read_word(_asciimap + k);
        if (!key) {
            setWriteError();
            return 0;
        }
        if ((key & SHIFT) == SHIFT) {
            _keyReport.modifiers |= 0x02;   // the left shift modifier
            key &= 0x00FF;
        }
    }
    k = (uint8_t)key;
    // Add k to the key report only if it's not already present
    // and if there is an empty slot.
    if (_keyReport.keys[0] != k && _keyReport.keys[1] != k &&
        _keyReport.keys[2] != k && _keyReport.keys[3] != k &&
        _keyReport.keys[4] != k && _keyReport.keys[5] != k) {

        for (i = 0; i < 6; i++) {
            if (_keyReport.keys[i] == 0x00) {
                _keyReport.keys[i] = k;
                break;
            }
        }
        if (i == 6) {
            setWriteError();
            return 0;
        }
    }
    sendReport(&_keyReport);
    return 1;
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t HID_Keyboard_Pico::release(uint8_t k)
{
    uint8_t i;
    uint16_t key;

    if (k > 0xE7) {
        setWriteError();
        return 0;
    } else if (k >= 0xE0) { // it's a modifier key
        _keyReport.modifiers &= ~(1<<(k-0xE0));
        key = 0;
    } else {                // it's a printing key
        key = pgm_read_word(_asciimap + k);
        if (!key) {
            return 0;
        }
        if ((key & SHIFT) == SHIFT) {
            _keyReport.modifiers &= ~(0x02);    // the left shift modifier
            key &= 0x00FF;
        }
    }
    k = (uint8_t)key;
    // Test the key report to see if k is present.  Clear it if it exists.
    // Check all positions in case the key is present more than once (which it shouldn't be)
    for (i = 0; i < 6; i++) {
        if (0 != k && _keyReport.keys[i] == k) {
            _keyReport.keys[i] = 0x00;
        }
    }

    sendReport(&_keyReport);
    return 1;
}
size_t HID_Keyboard_Pico::pressID(uint8_t k)
{
    uint8_t i;

    if (k > 0xE7) {
        setWriteError();
        return 0;
    } else if (k >= 0xE0) { // it's a modifier key
        _keyReport.modifiers |= (1<<(k-0xE0));
        k = 0;
    }
    // Add k to the key report only if it's not already present
    // and if there is an empty slot.
    if (_keyReport.keys[0] != k && _keyReport.keys[1] != k &&
        _keyReport.keys[2] != k && _keyReport.keys[3] != k &&
        _keyReport.keys[4] != k && _keyReport.keys[5] != k) {

        for (i = 0; i < 6; i++) {
            if (_keyReport.keys[i] == 0x00) {
                _keyReport.keys[i] = k;
                break;
            }
        }
        if (i == 6) {
            setWriteError();
            return 0;
        }
    }
    sendReport(&_keyReport);
    return 1;
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t HID_Keyboard_Pico::releaseID(uint8_t k)
{
    uint8_t i;

    if (k > 0xE7) {
        setWriteError();
        return 0;
    } else if (k >= 0xE0) { // it's a modifier key
        _keyReport.modifiers &= ~(1<<(k-0xE0));
        k = 0;
    }
    // Test the key report to see if k is present.  Clear it if it exists.
    // Check all positions in case the key is present more than once (which it shouldn't be)
    for (i = 0; i < 6; i++) {
        if (0 != k && _keyReport.keys[i] == k) {
            _keyReport.keys[i] = 0x00;
        }
    }

    sendReport(&_keyReport);
    return 1;
}

size_t HID_Keyboard_Pico::consumerPress(uint16_t k)
{
    sendConsumerReport(k);
    return 1;
}

size_t HID_Keyboard_Pico::consumerRelease()
{
    sendConsumerReport(0);
    return 1;
}

void HID_Keyboard_Pico::releaseAll(void)
{
    _keyReport.keys[0] = 0;
    _keyReport.keys[1] = 0;
    _keyReport.keys[2] = 0;
    _keyReport.keys[3] = 0;
    _keyReport.keys[4] = 0;
    _keyReport.keys[5] = 0;
    _keyReport.modifiers = 0;
    sendReport(&_keyReport);
}

size_t HID_Keyboard_Pico::write(uint8_t c)
{
    uint8_t p = press(c);  // Keydown
    delay(10);
    release(c);            // Keyup
    delay(10);
    return p;              // just return the result of press() since release() almost always returns 1
}

size_t HID_Keyboard_Pico::write(const uint8_t *buffer, size_t size) {
    size_t n = 0;
    while (size--) {
        if (*buffer != '\r') {
            if (write(*buffer)) {
                n++;
            } else {
                break;
            }
        }
        buffer++;
    }
    return n;
}

size_t HID_Keyboard_Pico::writeID(uint8_t k)
{
    uint8_t p = pressID(k);  // Keydown
    delay(10);
    releaseID(k);            // Keyup
    delay(10);
    return p;              // just return the result of press() since release() almost always returns 1
}

void HID_Keyboard_Pico::onLED(LedCallbackFcn fcn, void *cbData) {
    _ledCB = fcn;
    _ledCBdata = cbData;
}
