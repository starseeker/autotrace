//
// Created by nick on 7/30/18.
//

#include "InputOptionsBuilder.h"

InputOptionsBuilder InputOptionsBuilder::builder() {
  return InputOptionsBuilder();
}

InputOptions InputOptionsBuilder::build() {
  return inputOptions;
}

InputOptionsBuilder &InputOptionsBuilder::setBackgroudColor(_at_color color) {
  inputOptions.background_color = at_color_copy(&color);
  return *this;
}

InputOptionsBuilder &InputOptionsBuilder::setCharCode(unsigned int charCode) {
  inputOptions.charcode = charCode;
  return *this;
}
