#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by nick on 12/08/2018.
//

#include "InputOptions.h"
#include "InputOptionsBuilder.h"

#include <Json/JsonHelper.h>

#include <gtest/gtest.h>

using namespace json11;

TEST(InputOptionsTests, CorrectDefault) {
  InputOptions inputOptions;

  EXPECT_EQ(0, inputOptions.charcode);
  EXPECT_true(inputOptions.background_color != nullptr);
}

TEST(InputOptionsTests, FromJson) {
  const auto inputOptionJson = R"({"charcode": 13, "background_color": {"red": 128,"green": 129,"blue": 130}})";
  std::string jsonError;
  InputOptions inputOptions{Json::parse(inputOptionJson, jsonError, STANDARD)};
  EXPECT_true(jsonError.empty());

  EXPECT_EQ(13, inputOptions.charcode);
  ASSERT_true(inputOptions.background_color != nullptr);
  EXPECT_EQ(128, static_cast<uint16_t>(inputOptions.background_color->r));
  EXPECT_EQ(129, static_cast<uint16_t>(inputOptions.background_color->g));
  EXPECT_EQ(130, static_cast<uint16_t>(inputOptions.background_color->b));
}

TEST(InputOptionsTests, ToJson) {
  const auto inputOptions = InputOptionsBuilder::builder()
    .setBackgroudColor({20,21,22})
    .setCharCode(15)
    .build();

  const auto inputOptionsJson = inputOptions.toJson();
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
}

#pragma clang diagnostic pop
