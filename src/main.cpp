/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino Uno:  2, 3
     Arduino Due:  All pins, except 13 (LED)
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 3.0:   All pins, except 13 (LED)
     Teensy 2.0:   5, 6, 7, 8
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11
  
  for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
  Like the Original library and example this is under LGPL license.
  
  Modified by Cuninganreset@gmail.com on 2010-03-22
  Modified by Paul Stoffregen <paul@pjrc.com> June 2010
*/
   
#include <PS2Keyboard.h>
#include <BleKeyboard.h>

const int DataPin = 27;
const int IRQpin =  26;

PS2Keyboard keyboard;
BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  Serial.println("Keyboard Test:");
  keyboard.begin(DataPin, IRQpin, PS2Keymap_German);
  bleKeyboard.begin();
}

void loop() {
  if (!bleKeyboard.isConnected()) {
      return;
  }

  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();

    Serial.printf("Got: %02x\n", c);

   switch (c) {
      case PS2_ENTER:
        Serial.println();
        bleKeyboard.write(KEY_RETURN);
        break;
      case PS2_TAB:
        Serial.print("[Tab]");
        bleKeyboard.write(KEY_TAB);
        break;
      case PS2_ESC:
        Serial.print("[ESC]");
        bleKeyboard.write(KEY_ESC);
        break;
      case PS2_PAGEDOWN:
        Serial.print("[PgDn]");
        bleKeyboard.write(KEY_PAGE_DOWN);
        break;
      case PS2_PAGEUP:
        Serial.print("[PgUp]");
        bleKeyboard.write(KEY_PAGE_UP);
        break;
      case PS2_LEFTARROW:
        Serial.print("[Left]");
        bleKeyboard.write(KEY_LEFT_ARROW);
        break;
      case PS2_RIGHTARROW:
        Serial.print("[Right]");
        bleKeyboard.write(KEY_RIGHT_ARROW);
        break;
      case PS2_UPARROW:
        Serial.print("[Up]");
        bleKeyboard.write(KEY_UP_ARROW);
        break;
      case PS2_DOWNARROW:
        Serial.print("[Down]");
        bleKeyboard.write(KEY_DOWN_ARROW);
        break;
      case PS2_DELETE:
        Serial.print("\b \b");
        bleKeyboard.write(KEY_BACKSPACE);
        break;
      default:
        Serial.print(c);
        bleKeyboard.print(c);
        break;
    }
  }
}
