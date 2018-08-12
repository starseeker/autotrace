//
// Created by nick on 8/1/18.
//

#include "JsonHelper.h"

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