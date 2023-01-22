#include "gtest/gtest.h"
#include "LengthInLanguage.h"
#include <iostream>

int main() {
  /*std::string str;
  int l, k;
  std::cin >> str >> l >> k;
  std::cout << CheckLength::CheckIsInLanguage(str, l, k);*/
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}