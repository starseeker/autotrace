//
// Created by nick on 7/30/18.
//

#include "OutputOptionsBuilder.h"


OutputOptionsBuilder OutputOptionsBuilder::builder() {
  return OutputOptionsBuilder();
}

OutputOptions OutputOptionsBuilder::build() {
  return outputOpts;
}

OutputOptionsBuilder &OutputOptionsBuilder::setDpi(unsigned int dpi) {
  outputOpts.dpi = dpi;
  return *this;
}
