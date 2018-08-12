//
// Created by nick on 7/30/18.
//

#include "InputOptions.h"

#include <Json/JsonHelper.h>

InputOptions::InputOptions() : _at_input_opts_type() {
  background_color = new at_color();
  charcode = 0;
}

InputOptions::InputOptions(json11::Json inputOptionsJson) :
    InputOptions() {
  if (!inputOptionsJson.is_object()) {
    throw std::runtime_error("OutputOptions: top level is not an object." + inputOptionsJson.dump());
  }

  const auto &objectItems = inputOptionsJson.object_items();

  if(const auto maybeCharcode = JsonHelper::getNumber(objectItems, "charcode")) {
    charcode = static_cast<unsigned>(*maybeCharcode);
  }

  if (const auto maybeBackgroundColor = JsonHelper::getObject(objectItems, "background_color")) {
    const auto backgroundColor = *maybeBackgroundColor;

    const auto maybeRed = JsonHelper::getNumber(backgroundColor, "red");
    const auto maybeGreen = JsonHelper::getNumber(backgroundColor, "green");
    const auto maybeBlue = JsonHelper::getNumber(backgroundColor, "blue");

    if(!maybeRed || !maybeGreen || !maybeBlue) {
      throw std::runtime_error("OutputOptions: background_color red, green, blue should be present and numbers " + inputOptionsJson.dump());
    }

    const auto colorsInRange = [](const auto colorValue){ return colorValue > 0 && colorValue < 255; };

    if(!colorsInRange(*maybeRed) && !colorsInRange(maybeGreen) && !colorsInRange(maybeBlue)) {
      throw std::runtime_error("OutputOptions: background_color red, green, blue should be numbers between 0 and 255 " + inputOptionsJson.dump());
    }

    background_color->r = static_cast<uint8_t>(*maybeRed);
    background_color->g = static_cast<uint8_t>(*maybeGreen);
    background_color->b = static_cast<uint8_t>(*maybeBlue);
  }

}

json11::Json InputOptions::toJson() {
  return json11::Json();
}

InputOptions::~InputOptions() {
  delete background_color;
}
