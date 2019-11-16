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
    throw std::runtime_error("InputOptions: top level is not an object." + inputOptionsJson.dump());
  }

  const auto &objectItems = inputOptionsJson.object_items();

  if(const auto maybeCharcode = JsonHelper::getNumber(objectItems, "charcode")) {
    charcode = static_cast<unsigned>(*maybeCharcode);
  }

  if(const auto maybeColor = JsonHelper::getColor(objectItems, "background_color")) {
    background_color->r = maybeColor->r;
    background_color->g = maybeColor->g;
    background_color->b = maybeColor->b;
  }
}

json11::Json InputOptions::toJson() const {
  json11::Json::object inputObjectJson;
  inputObjectJson.emplace("charcode", (int)charcode);

  json11::Json::object backgroundColor;
  backgroundColor.emplace("red", background_color->r);
  backgroundColor.emplace("blue", background_color->b);
  backgroundColor.emplace("green", background_color->g);
  inputObjectJson.emplace("background_color", backgroundColor);

  return json11::Json{inputObjectJson};
}

InputOptions::~InputOptions() {
  delete background_color;
}

InputOptions::InputOptions(const InputOptions &other) : _at_input_opts_type(other) {
  background_color = new at_color();
  background_color->r = other.background_color->r;
  background_color->g = other.background_color->g;
  background_color->b = other.background_color->b;

  charcode = other.charcode;
}
