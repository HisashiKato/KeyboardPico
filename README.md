# KeyboardPicoJP

**Raspberry Pi Pico/RP2040 for Arduino の、USB HID キーボードライブラリ** </br>
**日本語キーボード配列対応版** </br>
### 概要
Raspberry Pi Pico/RP2040 for Arduino の USB HID キーボードライブラリを元にして、日本語キーボードレイアウトが追加出来るように改造したライブラリです。  
</br>
**素人改造。動作保証無し。サポート無し。使用は自己責任で。** </br>
**色々間違っていたらごめんなさい** </br>
</br>ノリと勢いだけで脳死状態で素人が書いたコードなので、一応チェックはしましたが絶対にバグが潜んでいると思います。  
**その道のプロの方、もしよろしければこれをフォークして、添削、修正して頂ければ幸いです。**  
</br>
### ライブラリのインストール方法
* Code から Download ZIP で保存
* Arduino IDE の スケッチ＞ライブラリをインクルード＞ZIP形式のライブラリをインストール で保存したZIPを選択  

### ライブラリの使用方法
基本的な使用方法は元になっている Keyboard library for Arduino と同じです。</br>
https://www.arduino.cc/reference/en/language/functions/usb/keyboard/ <br>
</br>
日本語キーボードのレイアウトに対応しました。
```
#include "KeyboardPico.h"

void setup() {
  Keyboard.begin(KeyboardLayout_ja_JP); // 日本語キーボードのレイアウト準拠
//Keyboard.begin(KeyboardLayout_en_US); // 英語(US)キーボードのレイアウト準拠
}
```
以下の関数を追加しました。
```
  size_t writeID(uint8_t k);
  size_t pressID(uint8_t k);
  size_t releaseID(uint8_t k);
```
上記 `uint8_t k` には、HIDキーボードの Usage ID を入れます。</br>
</br>
記述例

```
  /* [Ctrl]+[z] */
  {
    Keyboard.pressID(0xE0);     // UsaseID 0xE0  Keyboard LeftControl
    Keyboard.write('z');          // USB HID Keyboard Usage ID に関しては、
    Keyboard.releaseID(0xE0);     // Hut1_12v2.pdf  page 53  10 Keyboard/Keypad Page (0x07)
  }                               // を参照してください。

  /* [半角/全角 漢字]キー */
    Keyboard.writeID(0x35);         // UsaseID 0x35  Keyboard Grave Accent and Tilde
 or Keyboard.writeID(KEY_JP_KANJI); // KEY_JP_KANJI 0x35  KeyboardLayout_ja_JP.h 参照


  /* [変換 前候補 (次候補)]キー */
    Keyboard.writeID(0x8A);          // UsaseID 0x8A  Keyboard International4
 or Keyboard.writeID(KEY_JP_HENKAN); // KEY_JP_HENKAN 0x8A  KeyboardLayout_ja_JP.h 参照


  /* タスクマネージャー [Ctrl]＋[Shift]＋[Esc] */
  {
    Keyboard.pressID(KEY_LEFT_CTRL);  // KEY_LEFT_CTRL  0xE0  KeyboardLayout.h 参照
    Keyboard.pressID(KEY_LEFT_SHIFT); // KEY_LEFT_SHIFT 0xE1
    Keyboard.pressID(KEY_ESC);        // KEY_ESC        0x29
    Keyboard.releaseAll();
  }

  /* [Ctrl]+[Alt]+[Delete] */
  {
    Keyboard.pressID(KEY_LEFT_CTRL); // KEY_LEFT_CTRL 0xE0  KeyboardLayout.h 参照
    Keyboard.pressID(KEY_LEFT_ALT);  // KEY_LEFT_ALT  0xE2
    Keyboard.pressID(KEY_DELETE);    // KEY_DELETE    0x4C
    Keyboard.releaseAll();
  }
```

### 参考リンク
**Arduino 本家のキーボードライブラリ**  
https://www.arduino.cc/reference/en/language/functions/usb/keyboard/  
https://github.com/arduino-libraries/Keyboard  
</br>上記を元に [Raspberry Pi Pico Arduino core, for all RP2040 boards](https://github.com/earlephilhower/arduino-pico) 内に組み込まれたキーボードライブラリ  
https://github.com/earlephilhower/arduino-pico/tree/master/libraries/Keyboard  
</br>
**Arduino HID-Project**  
32u4 や SAMD21 の Arduino で USB HID デバイスを実現するライブラリ  
活用させて頂いています。そして参考にさせて頂きました。とても勉強になりました。  
https://github.com/NicoHood/HID
