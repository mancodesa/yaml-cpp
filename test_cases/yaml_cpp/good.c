#include "yaml-cpp/yaml.h"  // IWYU pragma: keep
#include "gtest/gtest.h"

#include <iostream>
#include <string>

namespace YAML {
namespace {

TEST(EmitterGoodTest, NewEmitterIsGood) {
  Emitter out;
  EXPECT_TRUE(out.good());
  EXPECT_EQ("", out.GetLastError());
}

TEST(EmitterGoodTest, GoodAfterValidOutput) {
  Emitter out;
  out << BeginSeq << 1 << 2 << EndSeq;
  EXPECT_TRUE(out.good());
}

TEST(EmitterGoodTest, NotGoodAfterMismatchedEnd) {
  Emitter out;
  out << BeginMap << EndSeq;
  EXPECT_FALSE(out.good());
  EXPECT_FALSE(out.GetLastError().empty());
}

TEST(EmitterGoodTest, NotGoodAfterBeginDocInGroup) {
  Emitter out;
  out << BeginSeq << BeginDoc;
  EXPECT_FALSE(out.good());
}

TEST(EmitterGoodTest, NotGoodAfterInvalidAnchor) {
  Emitter out;
  out << Anchor("bad anchor");
  EXPECT_FALSE(out.good());
}

TEST(EmitterGoodTest, StaysBadOnceBad) {
  Emitter out;
  out << BeginMap << EndSeq;
  EXPECT_FALSE(out.good());
  out << "more";
  EXPECT_FALSE(out.good());
}

}  // namespace
}  // namespace YAML
