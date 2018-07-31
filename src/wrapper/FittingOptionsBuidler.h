//
// Created by nick on 7/24/18.
//

#pragma once

#include "FittingOptions.h"

#include <src/autotrace.h>

class FittingOptionsBuilder {
public:
  static FittingOptionsBuilder builder();

  FittingOptionsBuilder &setBackgroudColor(_at_color color);

  FittingOptionsBuilder &setCharCode(unsigned int charCode);

  FittingOptionsBuilder &setColorCount(unsigned int colorCount);

  FittingOptionsBuilder &setCornerAlwaysThreshold(float threshold);

  FittingOptionsBuilder &setCornerSurround(unsigned int surround);

  FittingOptionsBuilder &setCornerThreshold(float threshold);

  FittingOptionsBuilder &setErrorThreshold(float threshold);

  FittingOptionsBuilder &setFilterIterations(unsigned int iterations);

  FittingOptionsBuilder &setLineReversionThreshold(float threshold);

  FittingOptionsBuilder &setLineThreshold(float threshold);

  FittingOptionsBuilder &setRemoveAdjacentCorners(bool remove);

  FittingOptionsBuilder &setTangentSurround(unsigned int tangentSurround);

  FittingOptionsBuilder &setDespeckleLevel(unsigned int despeckleLevel);

  FittingOptionsBuilder &setDespeckleTightness(unsigned int despeckleTightness);

  FittingOptionsBuilder &setNoiseRemoval(float removal);

  FittingOptionsBuilder &setCenterline(bool centerline);

  FittingOptionsBuilder &setPreserveWidth(bool preserve);

  FittingOptionsBuilder &setWidthWeightFactor(float weight);

  FittingOptions build();

private:

  FittingOptions fittingOpts;
};

