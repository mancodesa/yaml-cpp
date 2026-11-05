#include "yaml-cpp/yaml.h"  // IWYU pragma: keep
#include "gtest/gtest.h"

#include <iostream>
#include <string>

namespace YAML {
namespace {

TEST(EmitterEndDocTest, SimpleDoc) {
  Emitter out;
  out << BeginDoc << "foo" << EndDoc;
  EXPECT_TRUE(out.good());
  EXPECT_STREQ("---\nfoo\n...\n", out.c_str());
}

TEST(EmitterEndDocTest, EndDocAtColumnZero) {
  Emitter out;
  out << BeginDoc << EndDoc;
  EXPECT_TRUE(out.good());
}

TEST(EmitterEndDocTest, InsideGroupIsError) {
  Emitter out;
  out << BeginMap << EndDoc;
  EXPECT_FALSE(out.good());
  EXPECT_EQ("Unexpected begin document", out.GetLastError());
}

TEST(EmitterEndDocTest, AfterAnchorIsError) {
  Emitter out;
  out << Anchor("a") << EndDoc;
  EXPECT_FALSE(out.good());
}

TEST(EmitterEndDocTest, AfterTagIsError) {
  Emitter out;
  out << VerbatimTag("!foo") << EndDoc;
  EXPECT_FALSE(out.good());
}

TEST(EmitterEndDocTest, NoOpWhenAlreadyInError) {
  Emitter out;
  out << BeginMap << EndDoc;
  EXPECT_FALSE(out.good());
  std::string before = out.c_str();
  out << EndDoc;
  EXPECT_EQ(before, out.c_str());
}

TEST(EmitterEndDocTest, MultipleDocs) {
  Emitter out;
  out << BeginDoc << "a" << EndDoc << BeginDoc << "b" << EndDoc;
  EXPECT_TRUE(out.good());
  EXPECT_STREQ("---\na\n...\n---\nb\n...\n", out.c_str());
}

}  // namespace
}  // namespace YAML
