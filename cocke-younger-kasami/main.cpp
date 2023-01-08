#include "convert_to_chomsky.h"
#include "cyk.h"
#include "gtest/gtest.h"

int main() {
  int user = 0;
  std::cin >> user;
  if (user == 1) {
    std::string rule;
    int number_rules = 0;
    std::cin >> number_rules;
    Grammatica grammatica;
    while (number_rules > 0) {
      std::cin >> rule;
      grammatica.AddRule(rule);
      number_rules--;
    }
    std::string word;
    std::cin >> word;
    grammatica.ConvertToChomsky();
    CockeYoungerKasami cocke_younger_kasami;
    cocke_younger_kasami.SetForm(grammatica.GetChomskyForm());
    if (cocke_younger_kasami.IsInLanguage(word)) {
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