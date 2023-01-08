#include "earley.h"

bool Earley::IsInLanguage(const std::string& word) {
  word_ = word;
  situations_.resize(word.size() + 1);
  std::string S = "S";
  situations_[0].insert({{'\0', S}, 0, 0});
  for (size_t i = 0; i <= word.size(); i++) {
    Scan(i);
    size_t previous_size = situations_[i].size() + 1;
    while (previous_size != situations_[i].size()) {
      previous_size = situations_[i].size();
      Complete(i);
      Predict(i);
    }
  }
  if (situations_[word.size()].find({'\0', S, 1, 0}) != situations_[word.size()].end()) {
    return true;
  }
  return false;
}

void Earley::AddRule(const std::string& rule) {
  if (situations_.empty()) {
    situations_.resize(1);
  }
  rules_.insert({rule[0], rule.substr(3)});
}
bool operator<(const Rule& first, const Rule& second) {
  if (first.non_terminal < second.non_terminal) {
    return true;
  }
  if (first.non_terminal > second.non_terminal) {
    return false;
  }
  return first.rule < second.rule;
}
bool operator<(const Situation& first, const Situation& second) {
  if (first.rule_in_situation < second.rule_in_situation) {
    return true;
  }
  if (second.rule_in_situation < first.rule_in_situation) {
    return false;
  }
  if (first.not_in_alphabet_position < second.not_in_alphabet_position) {
    return true;
  }
  if (first.not_in_alphabet_position > second.not_in_alphabet_position) {
    return false;
  }
  return first.index < second.index;
}

bool Earley::HasSomethingAfterNotInAlphabetPosition(const Situation& situation) {
  return situation.not_in_alphabet_position < situation.rule_in_situation.rule.size();
}

char Earley::GetSymbolAfterNotInAlphabetPosition(const Situation& situation) {
  return situation.rule_in_situation.rule[situation.not_in_alphabet_position];
}

void Earley::Scan(size_t index) {
  if (index == 0) {
    return;
  }
  for (auto& situation : situations_[index - 1]) {
    if (HasSomethingAfterNotInAlphabetPosition(situation)
        && GetSymbolAfterNotInAlphabetPosition(situation) == word_[index - 1]) {
      situations_[index].insert({situation.rule_in_situation, situation.not_in_alphabet_position + 1, situation.index});
    }
  }
}

void Earley::Complete(size_t index) {
  for (auto& situation : situations_[index]) {
    if (!HasSomethingAfterNotInAlphabetPosition(situation)) {
      for (auto& index_situation : situations_[situation.index]) {
        if (HasSomethingAfterNotInAlphabetPosition(index_situation)
            && GetSymbolAfterNotInAlphabetPosition(index_situation) == situation.rule_in_situation.non_terminal) {
          situations_[index].insert({index_situation.rule_in_situation, index_situation.not_in_alphabet_position + 1,
                                     index_situation.index});
        }
      }
    }
  }
}

void Earley::Predict(size_t index) {
  for (auto& situation : situations_[index]) {
    if (HasSomethingAfterNotInAlphabetPosition(situation)) {
      for (auto& rule : rules_) {
        if (GetSymbolAfterNotInAlphabetPosition(situation) == rule.non_terminal) {
          situations_[index].insert({rule, 0, index});
        }
      }
    }
  }
}