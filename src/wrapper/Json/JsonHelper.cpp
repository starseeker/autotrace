//
// Created by nick on 8/1/18.
//

#include "JsonHelper.h"

#include <utility>

std::optional<int> JsonHelper::getNumber(Json::object jsonObject, std::string key) {
  const auto &jsonDpi = jsonObject.find(key);

  if (jsonDpi != jsonObject.end()) {
    if (!jsonDpi->second.is_number()) {
      return std::nullopt;
    }

    return jsonDpi->second.int_value();
  }

  return std::nullopt;
}

std::optional<Json::object> JsonHelper::getObject(Json::object jsonObject, std::string key) {
  const auto &jsonBackgroundColor = jsonObject.find(key);

  if (jsonBackgroundColor != jsonObject.end()) {
    if (jsonBackgroundColor->second.is_object()) {
      return jsonBackgroundColor->second.object_items();
    }
  }

  return std::nullopt;
}

std::optional<bool> JsonHelper::getBoolean(Json::object jsonObject, std::string key) {
  const auto &jsonBackgroundColor = jsonObject.find(key);

  if (jsonBackgroundColor != jsonObject.end()) {
    if (jsonBackgroundColor->second.is_bool()) {
      return jsonBackgroundColor->second.bool_value();
    }
  }

  return std::nullopt;
}

std::optional<at_color> JsonHelper::getColor(Json::object jsonObject, std::string key) {
  if (const auto maybeBackgroundColor = JsonHelper::getObject(std::move(jsonObject), key)) {
    const auto backgroundColor = *maybeBackgroundColor;

    const auto maybeRed = JsonHelper::getNumber(backgroundColor, "red");
    const auto maybeGreen = JsonHelper::getNumber(backgroundColor, "green");
    const auto maybeBlue = JsonHelper::getNumber(backgroundColor, "blue");

    if(!maybeRed || !maybeGreen || !maybeBlue) {
      return std::nullopt;
    }

    const auto colorsInRange = [](const auto colorValue){ return colorValue > 0 && colorValue < 255; };

    if(!colorsInRange(*maybeRed) && !colorsInRange(maybeGreen) && !colorsInRange(maybeBlue)) {
      return std::nullopt;
    }

    at_color color;

    color.r = static_cast<uint8_t>(*maybeRed);
    color.g = static_cast<uint8_t>(*maybeGreen);
    color.b = static_cast<uint8_t>(*maybeBlue);

    return color;
  }
  return std::nullopt;
}

std::optional<double> JsonHelper::getDecimal(Json::object jsonObject, std::string key) {
  const auto &jsonDpi = jsonObject.find(key);

  if (jsonDpi != jsonObject.end()) {
    if (!jsonDpi->second.is_number()) {
      return std::nullopt;
    }

    return jsonDpi->second.number_value();
  }

  return std::nullopt;
}
