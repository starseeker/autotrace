//
// Created by nick on 8/1/18.
//

#pragma once

#include "color.h"

#include <json11.hpp>

#include <optional>

using namespace json11;

namespace JsonHelper {
  std::optional<int> getNumber(Json::object jsonObject, std::string key);
  std::optional<Json::object> getObject(Json::object jsonObject, std::string key);
  std::optional<at_color> getColor(Json::object jsonObject, std::string key);
  std::optional<double> getDecimal(Json::object jsonObject, std::string key);
  std::optional<bool> getBoolean(Json::object jsonObject, std::string key);
};
