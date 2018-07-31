//
// Created by nick on 7/30/18.
//

#include "OutputOptions.h"

#include <gtest/gtest.h>

TEST(OutputOptionsTests, CorrectDefault) {
  OutputOptions outputOptions;

  EXPECT_EQ(72, outputOptions.dpi);
}
