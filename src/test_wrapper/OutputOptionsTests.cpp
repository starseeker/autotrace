#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by nick on 7/30/18.
//

#include "OutputOptions.h"
#include "OutputOptionsBuilder.h"

#include <gtest/gtest.h>

using namespace json11;

TEST(OutputOptionsTests, CorrectDefault) {
  OutputOptions outputOptions;

  EXPECT_EQ(72, outputOptions.dpi);
}

TEST(OutputOptionsTests, FromJson) {
  const auto outputOptionJson = "{ \"dpi\" : 13 }";
  std::string jsonError;
  OutputOptions outputOptions{Json::parse(outputOptionJson, jsonError, STANDARD)};
  EXPECT_true(jsonError.empty());

  EXPECT_EQ(13, outputOptions.dpi);
}

TEST(OutputOptionsTests, ToJson) {

  const auto expectDpi = [](const auto dpiValue) {
    const auto outputOptions = OutputOptionsBuilder::builder()
      .setDpi(dpiValue)
      .build();

    const auto outOptionsJson = outputOptions.toJson();
    EXPECT_true(outOptionsJson.is_object());
    const auto &objectItems = outOptionsJson.object_items();
    const auto &dpiItem = objectItems.find("dpi");
    EXPECT_true(dpiItem != objectItems.end());
    EXPECT_true(dpiItem->second.is_number());
    EXPECT_EQ(dpiValue, dpiItem->second.number_value());
  };

  expectDpi(72);
  expectDpi(15);
  expectDpi(-1);
  expectDpi(199999);
}


#pragma clang diagnostic pop
