#pragma once
#include <set>
#include <string>
#include <vector>

struct Rule {
  char non_terminal;
  std::string rule;
};
struct Situation {
  Rule rule_in_situation;
  size_t not_in_alphabet_position;
  size_t index;
};

class Earley {
 public:
  Earley() = default;
  void AddRule(const std::string&);
  bool IsInLanguage(const std::string&);

 private:
  void Scan(size_t);
  void Predict(size_t);
  void Complete(size_t);
  bool HasSomethingAfterNotInAlphabetPosition(const Situation&);
  char GetSymbolAfterNotInAlphabetPosition(const Situation&);
  std::set<Rule> rules_;
  std::string word_;
  std::vector<std::set<Situation>> situations_;
};