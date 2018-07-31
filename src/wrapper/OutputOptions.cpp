//
// Created by nick on 7/30/18.
//

#include "OutputOptions.h"

OutputOptions::OutputOptions() : _at_output_opts_type() {
  dpi = DEFAULT_DPI;
}

OutputOptions::OutputOptions(json11::Json outputOptionsJson) :
    OutputOptions() {
  if (!outputOptionsJson.is_object()) {
    throw std::runtime_error("OutputOptions: json is not an object " + outputOptionsJson.string_value());
  }

  const auto &objectItems = outputOptionsJson.object_items();

  const auto jsonDpi = objectItems.find("dpi");
  if (jsonDpi != objectItems.end()) {
    if (!jsonDpi->second.is_number()) {
      throw std::runtime_error("OutputOptions: dpi should be a number " + outputOptionsJson.string_value());
    }

    dpi = static_cast<unsigned int>(jsonDpi->second.number_value());
  }

  // TODO Parse Json
}

json11::Json OutputOptions::toJson() {
  // TODO create json
  return json11::Json();
}
