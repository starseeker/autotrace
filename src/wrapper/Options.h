//
// Created by Nick Winder on 6/10/18.
//

#pragma once

#include <src/bitmap.h>
#include <memory>

class Options {
public:
  Options(const at_fitting_opts_type &fittingOptions,
          const at_input_opts_type &inputOptions,
          const at_output_opts_type &outputOptions);

  const at_fitting_opts_type fittingOptions;
  const at_input_opts_type inputOptions;
  const at_output_opts_type outputOptions;
};

