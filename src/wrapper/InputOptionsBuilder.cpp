//
// Created by nick on 7/30/18.
//

#include "InputOptionsBuilder.h"

InputOptionsBuilder::InputOptionsBuilder() {
  input_opts_type.background_color = nullptr;
  input_opts_type.charcode = 0;
}

InputOptionsBuilder InputOptionsBuilder::builder() {
  return InputOptionsBuilder();
}

at_input_opts_type InputOptionsBuilder::build() {
  return input_opts_type;
}

InputOptionsBuilder &InputOptionsBuilder::setBackgroudColor(_at_color color) {
  input_opts_type.background_color = at_color_copy(&color);
  return *this;
}

InputOptionsBuilder &InputOptionsBuilder::setCharCode(unsigned int charCode) {
  input_opts_type.charcode = charCode;
  return *this;
}
