//
// Created by nick on 7/30/18.
//

#include "FittingOptions.h"


FittingOptions::FittingOptions() : fitting_opts_type() {
  background_color = nullptr;
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

FittingOptions::FittingOptions(json11::Json fittingOptionsJson) : FittingOptions() {
  // TODO Json
}

json11::Json FittingOptions::toJson() {
  // TODO Json
  return json11::Json();
}
