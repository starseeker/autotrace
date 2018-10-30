//
// Created by Nick Winder on 6/9/18.
//

#include "FittingOptionsBuidler.h"
#include "InputOptionsBuilder.h"
#include "OutputOptionsBuilder.h"

#include <src/wrapper/Autotrace.h>

#include <iostream>
#include <fstream>

using namespace json11;

const std::string assetPath = ASSET_PATH; // NOLINT
const auto inputPath = assetPath + "Test.png"; // NOLINT
const auto outputPath = assetPath + "test.svg"; //NOLINT

struct Result {
    bool success;
    std::string error;
};

struct ResultULongLong {
  bool success;
  std::string error;
  unsigned long value;
};

Result autotraceRun(const uintptr_t inputBuffer, const size_t inputBufferSize,
                    const std::string &fittingOptionsJson, const std::string &inputOptionsJson,
                    const std::string &outputOptionsJson) {
  std::string jsonError;
  auto jsonResult = Json::parse(fittingOptionsJson, jsonError, STANDARD);
  if (!jsonError.empty()) {
    return {false, "Fitting options json error : " + jsonError};
  }
  FittingOptions fittingOptions{jsonResult};

  jsonResult = Json::parse(inputOptionsJson, jsonError, STANDARD);
  if (!jsonError.empty()) {
    return {false, "Fitting options json error : " + jsonError};
  }
  InputOptions inputOptions{jsonResult};

  jsonResult = Json::parse(outputOptionsJson, jsonError, STANDARD);
  if (!jsonError.empty()) {
    return {false, "Fitting options json error : " + jsonError};
  }
  OutputOptions outputOptions{jsonResult};

  std::ofstream inputFile(inputPath, std::ofstream::binary);
  inputFile.write(reinterpret_cast<const char *const>(inputBuffer), inputBufferSize);
  inputFile.close();

  Options options{fittingOptions, inputOptions, outputOptions};
  Autotrace autotrace{inputPath, outputPath, options};
  const auto outputResult = autotrace.produceOutput();

  return {outputResult.has_value(), outputResult ? "" : outputResult.error()};
}

ResultULongLong outputFileSize() {
  std::ifstream in(outputPath, std::ifstream::ate | std::ifstream::binary);
  return {true, "", static_cast<unsigned long>(in.tellg())};
}

Result getOutputFile(const uintptr_t outputBuffer, const size_t outputBufferSize) {
  if (outputBufferSize < outputFileSize().value) {
    return {false, "Buffer is to small to recieve the file"};
  }
  std::ifstream in(outputPath, std::ifstream::binary);

  in.read(reinterpret_cast<char *>(outputBuffer), outputBufferSize);

  return {true, ""};
}

#ifdef EMSCRIPTEN
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(autotraceCpp) {
  value_object<Result>("Result")
    .field("success", &Result::success)
    .field("error", &Result::error)
    ;

  value_object<ResultULongLong>("ResultULongLong")
    .field("success", &ResultULongLong::success)
    .field("error", &ResultULongLong::error)
    .field("value", &ResultULongLong::value)
    ;

  function("autotraceRun", &autotraceRun, allow_raw_pointers());
  function("getOutputFile", &getOutputFile, allow_raw_pointers());
  function("outputFileSize", &outputFileSize);
}
#else

int main() {
  const FittingOptions fittingOptions = FittingOptionsBuilder::builder().build();
  const InputOptions inputOptions = InputOptionsBuilder::builder().build();
  const OutputOptions outputOptions = OutputOptionsBuilder::builder().build();

  Options options{fittingOptions, inputOptions, outputOptions};
  Autotrace autotrace{inputPath, outputPath, options};
  const auto outputResult = autotrace.produceOutput();
  if (!outputResult.has_value()) {
    std::cout << outputResult.error();
        return 1;
    }
  return 0;
}

#endif
