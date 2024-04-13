/*
  このライブラリの元になっている "Keyboard Library for Arduino" では、
  下に書かれている仕様のファイルを作成することで、キーボードレイアウトを
  変更することが可能になっているのですが、この仕様では日本語キーボードに
  存在する UsageID 0x87 以降の
  0x87 Keyboard International1 「\ _ ろ」キー、
  0x89 Keyboard International3 「\ | ー」キー、
  0x8A Keyboard International4 「変換 前候補」キー、
  などの変更や追加が出来ません。
  加えて "Keyboard Library for Arduino" では、_hidReportDescriptor の
  LOGICAL_MAXIMUM が(115)になっているので、0x74以降のキーIDの送信が不可能です。

  但し、Raspberry Pi Pico / RP2040 Arduino core の中に組み込まれている、
  "Keyboard Library for Arduino" を元にした HID_Keyboard ライブラリでは
  Raspberry Pi Pico の USB HID キーボードのレポートディスクリプタを使用するので、
  送信するキーIDの制限がありません。

  そこで、以前、"NicoHood Arduino HID-Project" ライブラリの、日本語キーボード
  レイアウトを作った時に得た知識を元にして、Arduino の Keboard ライブラリを
  独自に(勝手に)改造、仕様変更をして、日本語キーボードのレイアウトに
  対応させてみました。

  キーボードレイアウトのファイルの、レイアウト変換用の配列を 1byte から 2byte に
  変更しています。

  > extern const uint8_t KeyboardLayout_xx_YY[];

  > extern const uint16_t KeyboardLayout_ja_JP[];
                 ^^^^^^^^

  元のレイアウト変換用の配列が1バイトの中に修飾キーと文字コードを詰め込んでいる
  のに対して、この改造ライブラリのレイアウト変換用の配列は2バイトで、
  上位8ビットに修飾キー下位8ビットに文字コードを入れます。
  ライブラリ内部の処理も変更して、日本語キーボードのレイアウトに対応させました。

  以下は、この改造ライブラリの元になっているキーボードライブラリの、
  キーレイアウト変換ファイルの仕様です。
  =====================================================================

  KeyboardLayout.h

  This file is not part of the public API. It is meant to be included
  only in Keyboard.cpp and the keyboard layout files. Layout files map
  ASCII character codes to keyboard scan codes (technically, to USB HID
  Usage codes), possibly altered by the SHIFT or ALT_GR modifiers.

  == Creating your own layout ==

  In order to create your own layout file, copy an existing layout that
  is similar to yours, then modify it to use the correct keys. The
  layout is an array in ASCII order. Each entry contains a scan code,
  possibly modified by "|SHIFT" or "|ALT_GR", as in this excerpt from
  the Italian layout:

      0x35,          // bslash
      0x30|ALT_GR,   // ]
      0x2e|SHIFT,    // ^

  Do not change the control characters (those before scan code 0x2c,
  corresponding to space). Do not attempt to grow the table past DEL. Do
  not use both SHIFT and ALT_GR on the same character: this is not
  supported. Unsupported characters should have 0x00 as scan code.

  For a keyboard with an ISO physical layout, use the scan codes below:

      +---+---+---+---+---+---+---+---+---+---+---+---+---+-------+
      |35 |1e |1f |20 |21 |22 |23 |24 |25 |26 |27 |2d |2e |BackSp |
      +---+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-----+
      | Tab |14 |1a |08 |15 |17 |1c |18 |0c |12 |13 |2f |30 | Ret |
      +-----++--++--++--++--++--++--++--++--++--++--++--++--++    |
      |CapsL |04 |16 |07 |09 |0a |0b |0d |0e |0f |33 |34 |31 |    |
      +----+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+---+----+
      |Shi.|32 |1d |1b |06 |19 |05 |11 |10 |36 |37 |38 |  Shift   |
      +----+---++--+-+-+---+---+---+---+---+--++---+---++----+----+
      |Ctrl|Win |Alt |                        |AlGr|Win |Menu|Ctrl|
      +----+----+----+------------------------+----+----+----+----+

  The ANSI layout is identical except that key 0x31 is above (rather
  than next to) Return, and there is not key 0x32.

  Give a unique name to the layout array, then declare it in Keyboard.h
  with a line of the form:

    extern const uint8_t KeyboardLayout_xx_YY[];

  == Encoding details ==

  All scan codes are less than 0x80, which makes bit 7 available to
  signal that a modifier (Shift or AltGr) is needed to generate the
  character. With only one exception, keys that are used with modifiers
  have scan codes that are less than 0x40. This makes bit 6 available
  to signal whether the modifier is Shift or AltGr. The exception is
  0x64, the key next next to Left Shift on the ISO layout (and absent
  from the ANSI layout). We handle it by replacing its value by 0x32 in
  the layout arrays.
*/

#ifndef KEYBOARD_EN_US_h
#define KEYBOARD_EN_US_h

#endif
