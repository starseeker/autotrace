//
// Created by Nick Winder on 6/9/18.
//

#include "bitmap.h"
#include "FittingOptionsBuidler.h"
#include "InputOptionsBuilder.h"
#include "OutputOptionsBuilder.h"

#include <src/wrapper/Autotrace.h>

#include <iostream>

const std::string assetPath = ASSET_PATH; // NOLINT
const auto inputPath = assetPath + "antenna-architecture-building-443416.png"; // NOLINT
const auto outputPath = assetPath + "test.svg"; //NOLINT

int main() {
  const

  auto fittingOptions = FittingOptionsBuilder::builder().build();
  auto inputOptions = InputOptionsBuilder::builder().build();
  auto outputOptions = OutputOptionsBuilder::builder().build();

  Options options{fittingOptions, inputOptions, outputOptions};
  Autotrace autotrace{inputPath, outputPath, options};
  const auto outputResult = autotrace.produceOutput();
  if (!outputResult) {
    std::cout << "Error : " << outputResult.error() << std::endl;
  }

  std::cout << "Finished" << std::endl;

  return 0;
}
