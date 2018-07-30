//
// Created by Nick Winder on 6/10/18.
//

#include "Autotrace.h"
#include "Expected.h"

#include <src/logreport.h>

#include <fstream>
#include <src/filename.h>

Autotrace::Autotrace(const std::string &inputFile, const std::string &outputFile, const Options &options) : inputFile(
    inputFile), outputFilePath(outputFile), options(options) {
  autotrace_init();
}

nonstd::expected<void, std::string> Autotrace::produceOutput() {
  const auto inputReader = at_input_get_handler(const_cast<char *>(inputFile.c_str()));
  if (inputReader == nullptr) {
    return nonstd::make_unexpected("Input reader could not be found for " + inputFile);
  }

  const auto outputWriter = at_output_get_handler(const_cast<char *>(outputFilePath.c_str()));
  if (outputWriter == nullptr) {
    return nonstd::make_unexpected("Output writer cannot be determined for " + outputFilePath);
  }

  const auto outputFile = fopen(outputFilePath.c_str(), "wb");
  if (outputFile == nullptr) {
    return nonstd::make_unexpected("Unable to open file " + outputFilePath);
  }

  const auto bitmap = at_bitmap_read(inputReader, const_cast<char *>(inputFile.c_str()),
                                     const_cast<at_input_opts_type *>(&options.inputOptions), nullptr, nullptr);
//  if (report_progress) {
//    progress_reporter = dot_printer;
//    fprintf(stderr, "%-15s", input_name);
//  };

  int progress_stat = 0;

  const auto splines = at_splines_new_full(bitmap, const_cast<at_fitting_opts_type *>(&options.fittingOptions), nullptr,
                                           nullptr, nullptr, nullptr, nullptr, nullptr);

  at_splines_write(outputWriter, outputFile, const_cast<char *>(outputFilePath.c_str()),
                   const_cast<at_output_opts_type *>(&options.outputOptions), splines, nullptr, nullptr);

  fclose(outputFile);

  at_splines_free(splines);
  at_bitmap_free(bitmap);

//  if (report_progress)
//    fputs("\n", stderr);

  return nonstd::expected<void, std::string>();
}

static void dump(at_bitmap *bitmap, FILE *fp) {
  unsigned short width, height;
  unsigned int np;

  width = at_bitmap_get_width(bitmap);
  height = at_bitmap_get_height(bitmap);
  np = at_bitmap_get_planes(bitmap);

  for (int i = 0; i < width * height * np; ++i) {
    putc(AT_BITMAP_BITS(bitmap)[i], stdout);
  }
}
