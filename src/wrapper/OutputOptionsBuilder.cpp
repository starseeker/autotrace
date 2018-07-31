//
// Created by nick on 7/30/18.
//

#include "OutputOptionsBuilder.h"


OutputOptionsBuilder OutputOptionsBuilder::builder() {
  return OutputOptionsBuilder();
}

at_output_opts_type OutputOptionsBuilder::build() {
  return outputOpts;
}

OutputOptionsBuilder::OutputOptionsBuilder() {
  outputOpts.dpi = DEFAULT_DPI;
}

OutputOptionsBuilder &OutputOptionsBuilder::setDpi(unsigned int dpi) {
  outputOpts.dpi = dpi;
  return *this;
}
