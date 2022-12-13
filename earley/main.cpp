#include "earley.h"
#include "gtest/gtest.h"
#include <iostream>

int main() {
  int user = 0;
  std::cin >> user;
  if (user == 1) {
    std::string rule;
    int number_rules = 0;
    std::cin >> number_rules;
    Earley earley;
    while (number_rules > 0) {
      std::cin >> rule;
      earley.AddRule(rule);
      number_rules--;
    }
    std::string word;
    std::cin >> word;
    if (earley.IsInLanguage(word)) {
      std::cout << word << " is in language";
    } else {
      std::cout << word << " is not in language";
    }
    return 0;
  } else {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
  }
}