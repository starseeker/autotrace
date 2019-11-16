//
// Created by nick on 7/30/18.
//

#include "FittingOptions.h"

#include <Json/JsonHelper.h>

FittingOptions::FittingOptions() : fitting_opts_type() {
  background_color = new _at_color();
  charcode = 0;
  color_count = 0;
  corner_always_threshold = (float) 60.0;
  corner_surround = 4;
  corner_threshold = (float) 100.0;
  error_threshold = (float) 2.0;
  filter_iterations = 4;
  line_reversion_threshold = (float) .01;
  line_threshold = (float) 1.0;
  remove_adjacent_corners = false;
  tangent_surround = 3;
  despeckle_level = 0;
  despeckle_tightness = 2.0;
  noise_removal = (float) 0.99;
  centerline = false;
  preserve_width = false;
  width_weight_factor = 6.0;
}

FittingOptions::~FittingOptions() {
  delete background_color;
}

FittingOptions::FittingOptions(json11::Json fittingOptionsJson) : FittingOptions() {
  if (!fittingOptionsJson.is_object()) {
    throw std::runtime_error("FittingOptions: top level is not an object." + fittingOptionsJson.dump());
  }

  const auto &objectItems = fittingOptionsJson.object_items();

  if(const auto maybeColor = JsonHelper::getColor(objectItems, "background_color")) {
    background_color->r = maybeColor->r;
    background_color->g = maybeColor->g;
    background_color->b = maybeColor->b;
  }

  const auto setNumber = [&objectItems](unsigned& value, std::string key) {
    if(const auto maybeValue = JsonHelper::getNumber(objectItems, key)) {
      value = static_cast<unsigned>(*maybeValue);
    }
  };

  const auto setDecimal = [&objectItems](float& value, std::string key) {
    if(const auto maybeValue = JsonHelper::getDecimal(objectItems, key)) {
      value = *maybeValue;
    }
  };

  const auto setBoolean = [&objectItems](bool& value, std::string key) {
    if(const auto maybeValue = JsonHelper::getBoolean(objectItems, key)) {
      value = *maybeValue;
    }
  };

  setNumber(charcode, "charcode");
  setNumber(color_count, "color_count");
  setNumber(corner_surround, "corner_surround");
  setNumber(filter_iterations, "filter_iterations");
  setNumber(tangent_surround, "tangent_surround");
  setNumber(despeckle_level, "despeckle_level");
  setDecimal(corner_threshold, "corner_threshold");
  setDecimal(error_threshold, "error_threshold");
  setDecimal(corner_always_threshold, "corner_always_threshold");
  setDecimal(corner_always_threshold, "corner_always_threshold");
  setDecimal(line_reversion_threshold, "line_reversion_threshold");
  setDecimal(line_threshold, "line_threshold");
  setDecimal(despeckle_tightness, "despeckle_tightness");
  setDecimal(noise_removal, "noise_removal");
  setDecimal(width_weight_factor, "width_weight_factor");
  setBoolean(remove_adjacent_corners, "remove_adjacent_corners");
  setBoolean(centerline, "centerline");
  setBoolean(preserve_width, "preserve_width");
}

json11::Json FittingOptions::toJson() const {
  json11::Json::object fittingOptionsJson;
  fittingOptionsJson.emplace("charcode", (int)charcode);

  json11::Json::object backgroundColor;
  backgroundColor.emplace("red", background_color->r);
  backgroundColor.emplace("blue", background_color->b);
  backgroundColor.emplace("green", background_color->g);
  fittingOptionsJson.emplace("background_color", backgroundColor);

  fittingOptionsJson.emplace("color_count", (int)color_count);
  fittingOptionsJson.emplace("corner_surround", (int)corner_surround);
  fittingOptionsJson.emplace("filter_iterations", (int)filter_iterations);
  fittingOptionsJson.emplace("tangent_surround", (int)tangent_surround);
  fittingOptionsJson.emplace("despeckle_level", (int)despeckle_level);
  fittingOptionsJson.emplace("corner_threshold", corner_threshold);
  fittingOptionsJson.emplace("error_threshold", error_threshold);
  fittingOptionsJson.emplace("corner_always_threshold", corner_always_threshold);
  fittingOptionsJson.emplace("corner_always_threshold", corner_always_threshold);
  fittingOptionsJson.emplace("line_reversion_threshold", line_reversion_threshold);
  fittingOptionsJson.emplace("line_threshold", line_threshold);
  fittingOptionsJson.emplace("despeckle_tightness", despeckle_tightness);
  fittingOptionsJson.emplace("noise_removal", noise_removal);
  fittingOptionsJson.emplace("width_weight_factor", width_weight_factor);
  fittingOptionsJson.emplace("remove_adjacent_corners", remove_adjacent_corners);
  fittingOptionsJson.emplace("centerline", centerline);
  fittingOptionsJson.emplace("preserve_width", preserve_width);

  return fittingOptionsJson;
}

FittingOptions::FittingOptions(const FittingOptions &other) : _at_fitting_opts_type(other) {
  background_color = new at_color();
  background_color->r = other.background_color->r;
  background_color->g = other.background_color->g;
  background_color->b = other.background_color->b;

  charcode = other.charcode;
  color_count = other.color_count;
  corner_always_threshold = other.corner_always_threshold;
  corner_surround = other.corner_surround;
  corner_threshold = other.corner_threshold;
  error_threshold = other.error_threshold;
  filter_iterations = other.filter_iterations;
  line_reversion_threshold = other.line_reversion_threshold;
  line_threshold = other.line_threshold;
  remove_adjacent_corners = other.remove_adjacent_corners;
  tangent_surround = other.tangent_surround;
  despeckle_level = other.despeckle_level;
  despeckle_tightness = other.despeckle_tightness;
  noise_removal = other.noise_removal;
  centerline = other.centerline;
  preserve_width = other.preserve_width;
  width_weight_factor = other.width_weight_factor;
}
