//
// Created by nick on 7/30/18.
//

#include "OutputOptions.h"

#include <Json/JsonHelper.h>

OutputOptions::OutputOptions() : _at_output_opts_type() {
  dpi = DEFAULT_DPI;
}

OutputOptions::OutputOptions(json11::Json outputOptionsJson) :
    OutputOptions() {
  if (!outputOptionsJson.is_object()) {
    throw std::runtime_error("OutputOptions: top level is not an object." + outputOptionsJson.dump());
  }

  const auto &objectItems = outputOptionsJson.object_items();

  if(const auto maybeDpi = JsonHelper::getNumber(objectItems, "dpi")) {
    dpi = *maybeDpi;
  }
}

json11::Json OutputOptions::toJson() {
  json11::Json::object outputObjectJson;
  outputObjectJson.emplace("dpi", dpi);
  return json11::Json{outputObjectJson};
}
