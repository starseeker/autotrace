//
// Created by nick on 7/30/18.
//

#pragma once

#include "OutputOptions.h"

class OutputOptionsBuilder {
public:
  static OutputOptionsBuilder builder();

  OutputOptionsBuilder &setDpi(unsigned int dpi);

  OutputOptions build();

private:
  OutputOptions outputOpts;
};

