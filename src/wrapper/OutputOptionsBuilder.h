//
// Created by nick on 7/30/18.
//

#pragma once

#include <src/autotrace.h>

class OutputOptionsBuilder {
public:
  static OutputOptionsBuilder builder();

  OutputOptionsBuilder &setDpi(unsigned int dpi);

  at_output_opts_type build();

private:
  OutputOptionsBuilder();

  at_output_opts_type outputOpts;

  const unsigned int DEFAULT_DPI = 72;
};

