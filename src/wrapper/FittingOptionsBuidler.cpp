//
// Created by nick on 7/24/18.
//

#include "FittingOptionsBuidler.h"

#include <algorithm>

FittingOptionsBuilder FittingOptionsBuilder::builder() {
  return FittingOptionsBuilder();
}

at_fitting_opts_type FittingOptionsBuilder::build() {
  return fittingOpts;
}

FittingOptionsBuilder &FittingOptionsBuilder::setBackgroudColor(_at_color color) {
  fittingOpts.background_color = at_color_copy(&color);
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setCharCode(unsigned int charCode) {
  fittingOpts.charcode = charCode;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setColorCount(unsigned int colorCount) {
  fittingOpts.color_count = colorCount;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setCornerAlwaysThreshold(float threshold) {
  fittingOpts.corner_always_threshold = threshold;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setCornerSurround(unsigned int surround) {
  fittingOpts.corner_surround = surround;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setCornerThreshold(float threshold) {
  fittingOpts.corner_threshold = threshold;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setErrorThreshold(float threshold) {
  fittingOpts.error_threshold = threshold;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setFilterIterations(unsigned int iterations) {
  fittingOpts.filter_iterations = iterations;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setLineReversionThreshold(float threshold) {
  fittingOpts.line_reversion_threshold = threshold;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setLineThreshold(float threshold) {
  fittingOpts.line_threshold = threshold;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setRemoveAdjacentCorners(bool remove) {
  fittingOpts.remove_adjacent_corners = remove;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setTangentSurround(unsigned int tangentSurround) {
  fittingOpts.tangent_surround = tangentSurround;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setDespeckleLevel(unsigned int despeckleLevel) {
  fittingOpts.despeckle_level = despeckleLevel;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setDespeckleTightness(unsigned int despeckleTightness) {
  fittingOpts.despeckle_tightness = despeckleTightness;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setNoiseRemoval(float removal) {
  fittingOpts.noise_removal = removal;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setCenterline(bool centerline) {
  fittingOpts.centerline = centerline;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setPreserveWidth(bool preserve) {
  fittingOpts.preserve_width = preserve;
  return *this;
}

FittingOptionsBuilder &FittingOptionsBuilder::setWidthWeightFactor(float weight) {
  fittingOpts.width_weight_factor = weight;
  return *this;
}


