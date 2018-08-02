//
// Created by nick on 7/30/18.
//

#pragma once

#include <src/autotrace.h>
#include <json11.hpp>

class InputOptions : public at_input_opts_type {
public:
  InputOptions();

  virtual ~InputOptions();

  explicit InputOptions(json11::Json inputOptionsJson);

  json11::Json toJson();
};
