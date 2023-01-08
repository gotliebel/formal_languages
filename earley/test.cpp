#include "gtest/gtest.h"
#include "earley.h"

TEST(Earley, 1) {
  Earley earley;
  earley.AddRule("S->abc");
  ASSERT_EQ(earley.IsInLanguage("abc"), 1);
}

TEST(Earley, 2) {
  Earley earley;
  earley.AddRule("S->ABC");
  earley.AddRule("A->a");
  earley.AddRule("B->b");
  earley.AddRule("C->c");
  ASSERT_EQ(earley.IsInLanguage("abc"), 1);
}

TEST(Earley, 3) {
  Earley earley;
  earley.AddRule("S->Ab");
  earley.AddRule("A->a");
  ASSERT_EQ(earley.IsInLanguage("ab"), 1);
}

TEST(Earley, 4) {
  Earley earley;
  earley.AddRule("S->AB");
  earley.AddRule("C->c");
  earley.AddRule("A->a");
  earley.AddRule("B->b");
  ASSERT_EQ(earley.IsInLanguage("ab"), 1);
}

TEST(Earley, 5) {
  Earley earley;
  earley.AddRule("S->CD");
  earley.AddRule("C->c");
  earley.AddRule("D->d");
  ASSERT_EQ(earley.IsInLanguage("ab"), 0);
}

TEST(Earley, 6) {
  Earley earley;
  earley.AddRule("S->AB");
  earley.AddRule("S->");
  earley.AddRule("A->a");
  earley.AddRule("B->b");
  earley.AddRule("C->d");
  ASSERT_EQ(earley.IsInLanguage(""), 1);
}

TEST(Earley, 7) {
  Earley earley;
  earley.AddRule("S->AF");
  earley.AddRule("A->B");
  earley.AddRule("B->C");
  earley.AddRule("C->D");
  earley.AddRule("D->E");
  earley.AddRule("E->a");
  earley.AddRule("F->c");
  ASSERT_EQ(earley.IsInLanguage("ac"), 1);
}

TEST(Earley, 8) {
  Earley earley;
  earley.AddRule("S->ABa");
  earley.AddRule("A->c");
  earley.AddRule("B->b");
  ASSERT_EQ(earley.IsInLanguage("cba"), 1);
}

TEST(Earley, 9) {
  Earley earley;
  earley.AddRule("S->");
  earley.AddRule("S->(S)S");
  ASSERT_EQ(earley.IsInLanguage("()"), 1);
}

TEST(Earley, 10) {
  Earley earley;
  earley.AddRule("S->");
  earley.AddRule("S->(S)S");
  ASSERT_EQ(earley.IsInLanguage("()()"), 1);
}

TEST(Earley, 11) {
  Earley earley;
  earley.AddRule("S->");
  earley.AddRule("S->(S)S");
  ASSERT_EQ(earley.IsInLanguage("(()"), 0);
  ASSERT_EQ(earley.IsInLanguage(")(("), 0);
}
