#include "cyk.h"

void CockeYoungerKasami::SetForm(const std::unordered_map<char, std::vector<std::string>>& form) {
  chomsky_form_ = form;
}

bool CockeYoungerKasami::IsInLanguage(const std::string& word) {
  dp_.reserve(chomsky_form_.size());
  for (auto& element : chomsky_form_) {
    dp_[element.first].resize(word.size());
    for (size_t i = 0; i < word.size(); i++) {
      dp_[element.first][i].resize(word.size(), false);
    }
  }
  for (size_t i = 0; i < word.size(); i++) {
    for (auto& conversion : chomsky_form_) {
      for (auto& rule : conversion.second) {
        if (rule[0] == word[i]) {
          dp_[conversion.first][i][i] = true;
        }
      }
    }
  }

  for (size_t i = 0; i < word.size(); i++) {
    for (size_t j = 0; j < word.size() - i; j++) {
      for (auto& conversion : chomsky_form_) {
        for (size_t k = j; k < i + j; k++) {
          for (auto& rule : chomsky_form_[conversion.first]) {
            if (rule.size() == 2) {
              dp_[conversion.first][j][i + j] =
                  (dp_[conversion.first][j][i + j] || (dp_[rule[0]][j][k] && dp_[rule[1]][k + 1][i + j]));
            }
          }
        }
      }
    }
  }

  return dp_['S'][0][word.size() - 1];
}