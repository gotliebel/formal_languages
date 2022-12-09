#include "gtest/gtest.h"
#include "convert_to_chomsky.h"
#include "cyk.h"


TEST(CockeYoungerKasami, 1) {
  Grammatica grammatica;
  CockeYoungerKasami cyk;
  grammatica.AddRule("S->abc");
  grammatica.ConvertToChomsky();
  cyk.SetForm(grammatica.GetChomskyForm());
  ASSERT_EQ(cyk.IsInLanguage("abc"), 1);
}

TEST(CockeYoungerKasami, 2) {
  Grammatica grammatica;
  CockeYoungerKasami cyk;
  grammatica.AddRule("S->ABC");
  grammatica.AddRule("A->a");
  grammatica.AddRule("B->b");
  grammatica.AddRule("C->c");
  grammatica.ConvertToChomsky();
  cyk.SetForm(grammatica.GetChomskyForm());
  ASSERT_EQ(cyk.IsInLanguage("abc"), 1);
}

TEST(CockeYoungerKasami, 3) {
  Grammatica grammatica;
  CockeYoungerKasami cyk;
  grammatica.AddRule("S->Ab");
  grammatica.AddRule("A->a");
  grammatica.ConvertToChomsky();
  cyk.SetForm(grammatica.GetChomskyForm());
  ASSERT_EQ(cyk.IsInLanguage("ab"), 1);
}

TEST(CockeYoungerKasami, 4) {
  Grammatica grammatica;
  CockeYoungerKasami cyk;
  grammatica.AddRule("S->AB");
  grammatica.AddRule("C->c");
  grammatica.AddRule("A->a");
  grammatica.AddRule("B->b");
  grammatica.ConvertToChomsky();
  cyk.SetForm(grammatica.GetChomskyForm());
  ASSERT_EQ(cyk.IsInLanguage("ab"), 1);
}

TEST(CockeYoungerKasami, 5) {
  Grammatica grammatica;
  CockeYoungerKasami cyk;
  grammatica.AddRule("S->CD");
  grammatica.AddRule("C->c");
  grammatica.AddRule("D->d");
  grammatica.ConvertToChomsky();
  cyk.SetForm(grammatica.GetChomskyForm());
  ASSERT_EQ(cyk.IsInLanguage("ab"), 0);
}

TEST(CockeYoungerKasami, 6) {
  Grammatica grammatica;
  CockeYoungerKasami cyk;
  grammatica.AddRule("S->AB|*");
  grammatica.AddRule("A->a");
  grammatica.AddRule("B->b");
  grammatica.AddRule("C->d");
  grammatica.ConvertToChomsky();
  cyk.SetForm(grammatica.GetChomskyForm());
  ASSERT_EQ(cyk.IsInLanguage("*"), 1);
}

TEST(CockeYoungerKasami, 7) {
  Grammatica grammatica;
  CockeYoungerKasami cyk;
  grammatica.AddRule("S->AF");
  grammatica.AddRule("A->B");
  grammatica.AddRule("B->C");
  grammatica.AddRule("C->D");
  grammatica.AddRule("D->E");
  grammatica.AddRule("E->a");
  grammatica.AddRule("F->c");
  grammatica.ConvertToChomsky();
  cyk.SetForm(grammatica.GetChomskyForm());
  ASSERT_EQ(cyk.IsInLanguage("ac"), 1);
}

TEST(CockeYoungerKasami, 8) {
  Grammatica grammatica;
  CockeYoungerKasami cyk;
  grammatica.AddRule("S->ABa");
  grammatica.AddRule("A->c");
  grammatica.AddRule("B->b");
  grammatica.ConvertToChomsky();
  cyk.SetForm(grammatica.GetChomskyForm());
  ASSERT_EQ(cyk.IsInLanguage("cba"), 1);
}