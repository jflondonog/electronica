/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Fast.h"

String Fast::res(String res) {
  _res = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  if (res == "") {
    return _res;
  } else {
    return _res + res;
  }
}
