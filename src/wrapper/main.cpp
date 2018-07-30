//
// Created by Nick Winder on 6/9/18.
//

#include "bitmap.h"

#include <src/wrapper/Autotrace.h>

#include <iostream>

const std::string assetPath = ASSET_PATH;
const std::string inputPath = assetPath + "antenna-architecture-building-443416.png";
const std::string outputPath = assetPath + "test.svg";

int main() {
  const

  auto fittingOptions = *at_fitting_opts_new();
  auto inputOptions = *at_input_opts_new();
  auto outputOptions = *at_output_opts_new();

  Options options{fittingOptions, inputOptions, outputOptions};
  Autotrace autotrace{inputPath, outputPath, options};
  const auto outputResult = autotrace.produceOutput();
  if (!outputResult) {
    std::cout << "Error : " << outputResult.error() << std::endl;
  }

  std::cout << "Finished" << std::endl;

  return 0;
}
