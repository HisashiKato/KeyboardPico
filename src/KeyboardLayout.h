/*
  KeyboardLayout.h

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

#ifndef KEYBOARDLAYOUT_h
#define KEYBOARDLAYOUT_h

#include <Arduino.h>

//================================================================================
//================================================================================
//  Keyboard

// Modifiers
#define KEY_LEFT_CTRL     0xE0
#define KEY_LEFT_SHIFT    0xE1
#define KEY_LEFT_ALT      0xE2
#define KEY_LEFT_GUI      0xE3
#define KEY_RIGHT_CTRL    0xE4
#define KEY_RIGHT_SHIFT   0xE5
#define KEY_RIGHT_ALT     0xE6
#define KEY_RIGHT_GUI     0xE7

// Misc keys
#define KEY_RETURN        0x28
#define KEY_ESC           0x29
#define KEY_BACKSPACE     0x2A
#define KEY_TAB           0x2B
#define KEY_CAPS_LOCK     0x39
#define KEY_PRINT_SCREEN  0x46 // Print Screen / SysRq
#define KEY_SCROLL_LOCK   0x47
#define KEY_PAUSE         0x48 // Pause / Break
#define KEY_INSERT        0x49
#define KEY_HOME          0x4A
#define KEY_PAGE_UP       0x4B
#define KEY_DELETE        0x4C
#define KEY_END           0x4D
#define KEY_PAGE_DOWN     0x4E
#define KEY_RIGHT_ARROW   0x4F
#define KEY_LEFT_ARROW    0x50
#define KEY_DOWN_ARROW    0x51
#define KEY_UP_ARROW      0x52
#define KEY_MENU          0x65 // "Keyboard Application" in USB standard

// Numeric keypad
#define KEY_NUM_LOCK      0x53
#define KEY_KP_SLASH      0x54
#define KEY_KP_ASTERISK   0x55
#define KEY_KP_MINUS      0x56
#define KEY_KP_PLUS       0x57
#define KEY_KP_ENTER      0x58
#define KEY_KP_1          0x59
#define KEY_KP_2          0x5A
#define KEY_KP_3          0x5B
#define KEY_KP_4          0x5C
#define KEY_KP_5          0x5D
#define KEY_KP_6          0x5E
#define KEY_KP_7          0x5F
#define KEY_KP_8          0x60
#define KEY_KP_9          0x61
#define KEY_KP_0          0x62
#define KEY_KP_DOT        0x63

// Function keys
#define KEY_F1            0x3A
#define KEY_F2            0x3B
#define KEY_F3            0x3C
#define KEY_F4            0x3D
#define KEY_F5            0x3E
#define KEY_F6            0x3F
#define KEY_F7            0x40
#define KEY_F8            0x41
#define KEY_F9            0x42
#define KEY_F10           0x43
#define KEY_F11           0x44
#define KEY_F12           0x45
#define KEY_F13           0x68
#define KEY_F14           0x69
#define KEY_F15           0x6A
#define KEY_F16           0x6B
#define KEY_F17           0x6C
#define KEY_F18           0x6D
#define KEY_F19           0x6E
#define KEY_F20           0x6F
#define KEY_F21           0x70
#define KEY_F22           0x71
#define KEY_F23           0x72
#define KEY_F24           0x73


// Cpnsumer keys, taken from TinyUSB

// Power Control
#define KEY_POWER                              0x0030
#define KEY_RESET                              0x0031
#define KEY_SLEEP                              0x0032

// Screen Brightness
#define KEY_BRIGHTNESS_INCREMENT               0x006F
#define KEY_BRIGHTNESS_DECREMENT               0x0070

// These HID usages operate only on mobile systems (battery powered) and
// require Windows 8 (build 8302 or greater).
#define KEY_WIRELESS_RADIO_CONTROLS            0x000C
#define KEY_WIRELESS_RADIO_BUTTONS             0x00C6
#define KEY_WIRELESS_RADIO_LED                 0x00C7
#define KEY_WIRELESS_RADIO_SLIDER_SWITCH       0x00C8

// Media Control
#define KEY_PLAY_PAUSE                         0x00CD
#define KEY_SCAN_NEXT                          0x00B5
#define KEY_SCAN_PREVIOUS                      0x00B6
#define KEY_STOP                               0x00B7
#define KEY_VOLUME                             0x00E0
#define KEY_MUTE                               0x00E2
#define KEY_BASS                               0x00E3
#define KEY_TREBLE                             0x00E4
#define KEY_BASS_BOOST                         0x00E5
#define KEY_VOLUME_INCREMENT                   0x00E9
#define KEY_VOLUME_DECREMENT                   0x00EA
#define KEY_BASS_INCREMENT                     0x0152
#define KEY_BASS_DECREMENT                     0x0153
#define KEY_TREBLE_INCREMENT                   0x0154
#define KEY_TREBLE_DECREMENT                   0x0155

// Application Launcher
#define KEY_AL_CONSUMER_CONTROL_CONFIGURATION  0x0183
#define KEY_AL_EMAIL_READER                    0x018A
#define KEY_AL_CALCULATOR                      0x0192
#define KEY_AL_LOCAL_BROWSER                   0x0194

// Browser/Explorer Specific
#define KEY_AC_SEARCH                          0x0221
#define KEY_AC_HOME                            0x0223
#define KEY_AC_BACK                            0x0224
#define KEY_AC_FORWARD                         0x0225
#define KEY_AC_STOP                            0x0226
#define KEY_AC_REFRESH                         0x0227
#define KEY_AC_BOOKMARKS                       0x022A

// Mouse Horizontal scroll
#define KEY_AC_PAN                             0x0238


// keyboard layout
#define SHIFT 0x0200
// Supported keyboard layouts
#include "KeyboardLayout_en_US.h"
#include "KeyboardLayout_ja_JP.h"

extern const uint16_t KeyboardLayout_en_US[];
extern const uint16_t KeyboardLayout_ja_JP[];

#endif
