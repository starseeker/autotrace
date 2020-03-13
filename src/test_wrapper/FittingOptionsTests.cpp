#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by nick on 12/08/2018.
//

#include "FittingOptions.h"
#include "FittingOptionsBuidler.h"

#include <Json/JsonHelper.h>

#include <gtest/gtest.h>

using namespace json11;

TEST(FittingOptionsTests, CorrectDefault) {
  FittingOptions fittingOptions;

  EXPECT_EQ(0, fittingOptions.charcode);
  EXPECT_true(fittingOptions.background_color != nullptr);
  EXPECT_EQ(0, fittingOptions.color_count);
  EXPECT_EQ(60.0f, fittingOptions.corner_always_threshold);
  EXPECT_EQ(4, fittingOptions.corner_surround);
  EXPECT_EQ(100.0f, fittingOptions.corner_threshold);
  EXPECT_EQ(2.0f, fittingOptions.error_threshold);
  EXPECT_EQ(4, fittingOptions.filter_iterations);
  EXPECT_EQ(0.01f, fittingOptions.line_reversion_threshold);
  EXPECT_EQ(1.0f, fittingOptions.line_threshold);
  EXPECT_EQ(false, fittingOptions.remove_adjacent_corners);
  EXPECT_EQ(3, fittingOptions.tangent_surround);
  EXPECT_EQ(0, fittingOptions.despeckle_level);
  EXPECT_EQ(2.0f, fittingOptions.despeckle_tightness);
  EXPECT_EQ(0.99f, fittingOptions.noise_removal);
  EXPECT_EQ(false, fittingOptions.centerline);
  EXPECT_EQ(false, fittingOptions.preserve_width);
  EXPECT_EQ(6.0f, fittingOptions.width_weight_factor);
}

TEST(FittingOptionsTests, FromJson) {
  const auto fittingOptionJson = R"({
    "charcode": 13,
    "background_color": {
      "red": 128,
      "green": 129,
      "blue": 130
    },
    "color_count": 3,
    "corner_always_threshold": 40.0,
    "corner_surround": 3,
    "corner_threshold": 80.0,
    "error_threshold": 3.0,
    "filter_iterations": 2,
    "line_reversion_threshold": 3.0,
    "line_threshold": 2.0,
    "remove_adjacent_corners": true,
    "tangent_surround": 2,
    "despeckle_level": 1,
    "despeckle_tightness": 3.0,
    "noise_removal": 0.8,
    "centerline": true,
    "preserve_width": true,
    "width_weight_factor": 5.0
  })";

  std::string jsonError;
  FittingOptions fittingOptions{Json::parse(fittingOptionJson, jsonError, STANDARD)};
  EXPECT_true(jsonError.empty());

  EXPECT_EQ(13, fittingOptions.charcode);

  ASSERT_true(fittingOptions.background_color != nullptr);
  EXPECT_EQ(128, static_cast<uint16_t>(fittingOptions.background_color->r));
  EXPECT_EQ(129, static_cast<uint16_t>(fittingOptions.background_color->g));
  EXPECT_EQ(130, static_cast<uint16_t>(fittingOptions.background_color->b));

  EXPECT_EQ(3, fittingOptions.color_count);
  EXPECT_EQ(40.0f, fittingOptions.corner_always_threshold);
  EXPECT_EQ(3, fittingOptions.corner_surround);
  EXPECT_EQ(80.0f, fittingOptions.corner_threshold);
  EXPECT_EQ(3.0f, fittingOptions.error_threshold);
  EXPECT_EQ(2, fittingOptions.filter_iterations);
  EXPECT_EQ(3.0f, fittingOptions.line_reversion_threshold);
  EXPECT_EQ(2.0f, fittingOptions.line_threshold);
  EXPECT_EQ(true, fittingOptions.remove_adjacent_corners);
  EXPECT_EQ(2, fittingOptions.tangent_surround);
  EXPECT_EQ(1, fittingOptions.despeckle_level);
  EXPECT_EQ(3.0f, fittingOptions.despeckle_tightness);
  EXPECT_EQ(0.8f, fittingOptions.noise_removal);
  EXPECT_EQ(true, fittingOptions.centerline);
  EXPECT_EQ(true, fittingOptions.preserve_width);
  EXPECT_EQ(5.0f, fittingOptions.width_weight_factor);
}

TEST(FittingOptionsTests, ToJson) {

  const auto fittingOptions = FittingOptionsBuilder::builder()
    .setCharCode(15)
    .setBackgroudColor({20,21,22})
    .setColorCount(28)
    .setCornerAlwaysThreshold(160.0f)
    .setCornerSurround(8)
    .setCornerThreshold(90.0f)
    .setErrorThreshold(2.0f)
    .setFilterIterations(5)
    .setLineReversionThreshold(3.6f)
    .setLineThreshold(2.2f)
    .setRemoveAdjacentCorners(true)
    .setTangentSurround(3)
    .setDespeckleLevel(8)
    .setDespeckleTightness(5.0f)
    .setNoiseRemoval(0.9f)
    .setCenterline(true)
    .setPreserveWidth(true)
    .setWidthWeightFactor(6.0f)
    .build();

  const auto inputOptionsJson = fittingOptions.toJson();
  EXPECT_true(inputOptionsJson.is_object());
  const auto &objectItems = inputOptionsJson.object_items();

  const auto maybeCharcode = JsonHelper::getNumber(objectItems, "charcode");
  EXPECT_true(maybeCharcode);
  EXPECT_EQ(15, *maybeCharcode);

  const auto maybeBackground = JsonHelper::getObject(objectItems, "background_color");
  EXPECT_true(maybeBackground);
  const auto background = *maybeBackground;

  const auto maybeRed = JsonHelper::getNumber(background, "red");
  EXPECT_true(maybeRed);
  EXPECT_EQ(20, *maybeRed);

  const auto maybeGreen = JsonHelper::getNumber(background, "green");
  EXPECT_true(maybeGreen);
  EXPECT_EQ(21, *maybeGreen);

  const auto maybeBlue = JsonHelper::getNumber(background, "blue");
  EXPECT_true(maybeBlue);
  EXPECT_EQ(22, *maybeBlue);

  const auto maybeColorCount = JsonHelper::getNumber(objectItems, "color_count");
  EXPECT_true(maybeColorCount);
  EXPECT_EQ(28, *maybeColorCount);

  const auto maybeCornerAlwaysThreshold = JsonHelper::getDecimal(objectItems, "corner_always_threshold");
  EXPECT_true(maybeCornerAlwaysThreshold);
  EXPECT_EQ(160.0f, *maybeCornerAlwaysThreshold);

  const auto maybeCornerSurround = JsonHelper::getNumber(objectItems, "corner_surround");
  EXPECT_true(maybeCornerSurround);
  EXPECT_EQ(8, *maybeCornerSurround);

  const auto maybeCornerThreshold = JsonHelper::getDecimal(objectItems, "corner_threshold");
  EXPECT_true(maybeCornerThreshold);
  EXPECT_EQ(90.0f, *maybeCornerThreshold);

  const auto maybeErrorThreshold = JsonHelper::getDecimal(objectItems, "error_threshold");
  EXPECT_true(maybeErrorThreshold);
  EXPECT_EQ(2.0f, *maybeErrorThreshold);

  const auto maybeFilterIterations = JsonHelper::getNumber(objectItems, "filter_iterations");
  EXPECT_true(maybeFilterIterations);
  EXPECT_EQ(5, *maybeFilterIterations);

  const auto maybeLineReversionThreshold = JsonHelper::getDecimal(objectItems, "line_reversion_threshold");
  EXPECT_true(maybeLineReversionThreshold );
  EXPECT_EQ(3.6f, *maybeLineReversionThreshold );

  const auto maybeLineThreshold = JsonHelper::getDecimal(objectItems, "line_threshold");
  EXPECT_true(maybeLineThreshold);
  EXPECT_EQ(2.2f, *maybeLineThreshold);

  const auto maybeRemoveAdjacentCorners = JsonHelper::getBoolean(objectItems, "remove_adjacent_corners");
  EXPECT_true(maybeRemoveAdjacentCorners);
  EXPECT_EQ(true, *maybeRemoveAdjacentCorners);

  const auto maybeTangentSurround = JsonHelper::getNumber(objectItems, "tangent_surround");
  EXPECT_true(maybeTangentSurround);
  EXPECT_EQ(3, *maybeTangentSurround);

  const auto maybeDespeckleLevel = JsonHelper::getNumber(objectItems, "despeckle_level");
  EXPECT_true(maybeDespeckleLevel);
  EXPECT_EQ(8, *maybeDespeckleLevel);

  const auto maybeDespeckleTightness = JsonHelper::getDecimal(objectItems, "despeckle_tightness");
  EXPECT_true(maybeDespeckleTightness);
  EXPECT_EQ(5.0f, *maybeDespeckleTightness);

  const auto maybeNoiseRemoval = JsonHelper::getDecimal(objectItems, "noise_removal");
  EXPECT_true(maybeNoiseRemoval);
  EXPECT_EQ(0.9f, *maybeNoiseRemoval);

  const auto maybeCentreline = JsonHelper::getBoolean(objectItems, "centerline");
  EXPECT_true(maybeCentreline);
  EXPECT_EQ(true, *maybeCentreline);

  const auto maybePreserveWidth = JsonHelper::getBoolean(objectItems, "preserve_width");
  EXPECT_true(maybePreserveWidth);
  EXPECT_EQ(true, *maybePreserveWidth);

  const auto maybeWidthWeightFactor = JsonHelper::getDecimal(objectItems, "width_weight_factor");
  EXPECT_true(maybeWidthWeightFactor);
  EXPECT_EQ(6.0f, *maybeWidthWeightFactor);
}

#pragma clang diagnostic pop
