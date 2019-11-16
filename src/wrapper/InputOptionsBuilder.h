//
// Created by nick on 7/30/18.
//

#pragma once

#include "InputOptions.h"

class InputOptionsBuilder {
public:
  static InputOptionsBuilder builder();

  InputOptions build();

  InputOptionsBuilder &setBackgroudColor(_at_color color);

  InputOptionsBuilder &setCharCode(unsigned int charCode);

private:
  InputOptions inputOptions;
};

