//
// Created by nick on 7/30/18.
//

#pragma once

#include <src/fit.h>
#include <json11.hpp>

class FittingOptions : public fitting_opts_type {
public:
  FittingOptions();
  virtual ~FittingOptions();

  FittingOptions(const FittingOptions& other);
  FittingOptions& operator=(const FittingOptions& other) = default;

  explicit FittingOptions(json11::Json fittingOptionsJson);

  json11::Json toJson() const;
};
