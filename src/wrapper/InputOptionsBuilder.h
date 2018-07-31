//
// Created by nick on 7/30/18.
//

#pragma once


#include <src/autotrace.h>

class InputOptionsBuilder {
public:
  static InputOptionsBuilder builder();

  at_input_opts_type build();

  InputOptionsBuilder &setBackgroudColor(_at_color color);

  InputOptionsBuilder &setCharCode(unsigned int charCode);

private:
public:
  InputOptionsBuilder();

private:
  at_input_opts_type input_opts_type;

};

