#include "gtest/gtest.h"
#include "LengthInLanguage.h"

TEST(IsInLanguage, 1) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.a.", 4, 5), 0);
}
TEST(IsInLanguage, 2) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.a+", 4, 5), 0);
}
TEST(IsInLanguage, 3) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.a+", 1, 5), 1);
}
TEST(IsInLanguage, 4) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.aa.+", 4, 5), 0);
}
TEST(IsInLanguage, 5) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.aa.+*", 4, 10), 1);
}
TEST(IsInLanguage, 6) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.aa.a.+*", 1, 5), 1);
}
TEST(IsInLanguage, 7) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.*a.a.a.", 5, 10), 1);
}
TEST(IsInLanguage, 8) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.*aa.a.*", 4, 5), 1);
}
TEST(IsInLanguage, 9) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.a.a+*", 4, 6), 1);
}
TEST(IsInLanguage, 10) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.a.a.*a+", 3, 5), 1);
}
TEST(IsInLanguage, 11) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("a*", 0, 100), 1);
}
TEST(IsInLanguage, 12) {
  ASSERT_EQ(CheckLength::CheckIsInLanguage("aa.a.a+*",0,6), 1);
}