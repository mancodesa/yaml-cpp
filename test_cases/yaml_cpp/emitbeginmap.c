#include "yaml-cpp/yaml.h"  // IWYU pragma: keep
#include "gtest/gtest.h"

#include <iostream>
#include <string>

namespace YAML {
namespace {

TEST(EmitterBeginMapTest, BlockMap) {
  Emitter out;
  out << BeginMap << Key << "a" << Value << "b" << EndMap;
  EXPECT_TRUE(out.good());
  EXPECT_STREQ("a: b", out.c_str());
}

TEST(EmitterBeginMapTest, FlowMap) {
  Emitter out;
  out << Flow << BeginMap << Key << "a" << Value << "b" << Key << "c" << Value
      << "d" << EndMap;
  EXPECT_STREQ("{a: b, c: d}", out.c_str());
}

TEST(EmitterBeginMapTest, MapInSequence) {
  Emitter out;
  out << BeginSeq << BeginMap << Key << "a" << Value << "b" << EndMap
      << EndSeq;
  EXPECT_TRUE(out.good());
  EXPECT_STREQ("- a: b", out.c_str());
}

TEST(EmitterBeginMapTest, NestedMap) {
  Emitter out;
  out << BeginMap << Key << "a" << Value << BeginMap << Key << "b" << Value
      << "c" << EndMap << EndMap;
  EXPECT_TRUE(out.good());
  EXPECT_STREQ("a:\n  b: c", out.c_str());
}

TEST(EmitterBeginMapTest, MapAsKey) {
  Emitter out;
  out << BeginMap << Key << BeginMap << Key << "a" << Value << "b" << EndMap
      << Value << "c" << EndMap;
  EXPECT_TRUE(out.good());
}

TEST(EmitterBeginMapTest, LongKeyMap) {
  Emitter out;
  out << BeginMap << Key << "a" << Value << "b" << EndMap;
  EXPECT_TRUE(out.good());
}

TEST(EmitterBeginMapTest, NoOpWhenEmitterInErrorState) {
  Emitter out;
  out << BeginSeq << EndMap;
  EXPECT_FALSE(out.good());
  out << BeginMap << Key << "a";
  EXPECT_FALSE(out.good());
  EXPECT_STREQ("{}", out.c_str());
}

}  // namespace
}  // namespace YAML
