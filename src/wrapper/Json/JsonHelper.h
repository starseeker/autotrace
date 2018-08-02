//
// Created by nick on 8/1/18.
//

#pragma once


#include <json11.hpp>

#include <optional>

using namespace json11;

namespace JsonHelper {
  std::optional<int> getNumber(Json::object jsonObject, std::string key);
};
