//
// Created by nick on 7/30/18.
//

#pragma once

#include <src/autotrace.h>

#include <json11.hpp>

class OutputOptions : public at_output_opts_type {
public:
  OutputOptions();

  explicit OutputOptions(json11::Json outputOptionsJson);

  json11::Json toJson();

private:
  const unsigned int DEFAULT_DPI = 72;
};
