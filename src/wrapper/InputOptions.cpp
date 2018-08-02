//
// Created by nick on 7/30/18.
//

#include "InputOptions.h"

InputOptions::InputOptions() : _at_input_opts_type() {
  background_color = nullptr;
  charcode = 0;
}

InputOptions::InputOptions(json11::Json inputOptionsJson) :
    InputOptions() {
  if (!inputOptionsJson.is_object()) {
    throw std::runtime_error("OutputOptions: top level is not an object." + inputOptionsJson.dump());
  }

  const auto &objectItems = inputOptionsJson.object_items();

  const auto &jsonCharcode = objectItems.find("charcode");
  if (jsonCharcode != objectItems.end()) {
    if (!jsonCharcode->second.is_number()) {
      throw std::runtime_error("OutputOptions: dpi should be a number. " + inputOptionsJson.dump());
    }

    charcode = static_cast<unsigned int>(jsonCharcode->second.int_value());
  }

  const auto &jsonBackgroundColor = objectItems.find("background_color");
  if (jsonBackgroundColor != objectItems.end()) {
    if (!jsonBackgroundColor->second.is_object()) {
      throw std::runtime_error("OutputOptions: background_color should be a object. " + inputOptionsJson.dump());
    }

    const auto& colorObjectItems = jsonBackgroundColor->second.object_items();

    const auto &redJson = colorObjectItems.find("red");
    const auto &greenJson = colorObjectItems.find("green");
    const auto &blueJson = colorObjectItems.find("blue");

    if (redJson == colorObjectItems.end() && greenJson == colorObjectItems.end() && blueJson == colorObjectItems.end()) {
      throw std::runtime_error("OutputOptions: background_color red, green, blue should be present " + inputOptionsJson.dump());
    }

    if(!redJson->second.is_number() || !greenJson->second.is_number() || !blueJson->second.is_number()) {
      throw std::runtime_error("OutputOptions: background_color red, green, blue should be numbers " + inputOptionsJson.dump());
    }

    const auto red = redJson->second.number_value();
    const auto green = greenJson->second.number_value();
    const auto blue = blueJson->second.number_value();

    const auto colorsInRange = [](const auto colorValue){ return colorValue > 0 && colorValue < 255; };

    if(!colorsInRange(red) && !colorsInRange(green) && !colorsInRange(blue)) {
      throw std::runtime_error("OutputOptions: background_color red, green, blue should be numbers between 0 and 255 " + inputOptionsJson.dump());
    }

    if(background_color == nullptr) {
      background_color = new at_color();
    }

    background_color->r = static_cast<uint8_t>(red);
    background_color->g = static_cast<uint8_t>(green);
    background_color->b = static_cast<uint8_t>(blue);
  }

}

json11::Json InputOptions::toJson() {
  return json11::Json();
}

InputOptions::~InputOptions() {
  delete background_color;
}
