#include "convert_to_chomsky.h"

void Grammatica::AddRule(const std::string& rule) {
  std::string cur_rule;
  char begin_symbol = rule[0];
  size_t index = 1;
  non_terminal_.insert(rule[0]);
  for (size_t i = index + 2; i < rule.size(); i++) {
    if (rule[i] != '|') {
      cur_rule += rule[i];
      if (std::isupper(rule[i])) {
        non_terminal_.insert(rule[i]);
      } else {
        terminal_.insert(rule[i]);
      }
    } else {
      base_form_[begin_symbol].emplace_back(cur_rule);
      cur_rule.clear();
    }
  }
  base_form_[begin_symbol].emplace_back(cur_rule);
}

std::unordered_map<char, std::vector<std::string>> Grammatica::GetChomskyForm() const {
  return chomsky_form_;
}

void Grammatica::ConvertToChomsky() {
  DeleteNonReachable();
  DeleteMixed();
  DeleteLong();
  DeleteUnary();
}

bool Grammatica::IsTerminal(char symbol) {
  if (std::isupper(symbol)) {
    return false;
  }
  return true;
}

bool Grammatica::IsNonTerminal(char symbol) {
  if (non_terminal_.find(symbol) == non_terminal_.end()) {
    return false;
  }
  return true;
}

void Grammatica::DeleteNonReachable() {
  std::unordered_map<char, bool> is_non_reachable;
  for (auto& conversion : base_form_) {
    auto symbol = conversion.first;
    bool is_reachable = false;
    if (symbol == 'S') {
      is_reachable = true;
    }
    for (auto& check : base_form_) {
      for (auto& rule : check.second) {
        for (auto& c : rule) {
          if (c == symbol) {
            is_reachable = true;
            break;
          }
        }
        if (is_reachable) {
          break;
        }
      }
      if (is_reachable) {
        break;
      }
    }
    is_non_reachable[symbol] = !is_reachable;
  }
  for (auto& non_reachability : is_non_reachable) {
    if (!non_reachability.second) {
      chomsky_form_[non_reachability.first] = std::move(base_form_[non_reachability.first]);
    } else {
      non_terminal_.erase(non_reachability.first);
    }
  }
  base_form_.clear();
}

void Grammatica::DeleteMixed() {
  base_form_ = std::move(chomsky_form_);
  for (auto& conversion : base_form_) {
    for (auto& rule : conversion.second) {
      for (auto& symbol : rule) {
        if (IsTerminal(symbol)) {
          for (auto& a : alphabet_) {
            if (non_terminal_.find(a) == non_terminal_.end()) {
              non_terminal_.insert(a);
              chomsky_form_[a].push_back({symbol});
              symbol = a;
              break;
            }
          }
        }
      }
    }
  }
  for (auto& conversion : base_form_) {
    chomsky_form_[conversion.first] = std::move(base_form_[conversion.first]);
  }
  base_form_.clear();
}

void Grammatica::DeleteLong() {
  base_form_ = std::move(chomsky_form_);
  for (auto& conversion : base_form_) {
    for (auto& rule : conversion.second) {
      if (rule.size() > 2) {
        std::string new_rule;
        new_rule += rule[0];
        char previous_non_terminal;
        for (auto& a : alphabet_) {
          if (!IsNonTerminal(a)) {
            new_rule += a;
            previous_non_terminal = a;
            chomsky_form_[conversion.first].push_back(new_rule);
            non_terminal_.insert(a);
            break;
          }
        }
        for (size_t i = 1; i < rule.size(); i++) {
          new_rule.erase();
          for (auto& a : alphabet_) {
            if (!IsNonTerminal(a)) {
              new_rule += rule[i];
              if (i != rule.size() - 1) {
                new_rule += a;
              }
              chomsky_form_[previous_non_terminal].push_back(new_rule);
              previous_non_terminal = a;
              non_terminal_.insert(a);
              break;
            }
          }
        }
      } else {
        chomsky_form_[conversion.first].push_back(rule);
      }
    }
  }
}

void Grammatica::DeleteUnary() {
  base_form_ = std::move(chomsky_form_);
  std::unordered_map<char, std::vector<std::pair<std::string, bool>>> is_unary;
  for (auto& conversion : base_form_) {
    for (auto& rule : conversion.second) {
      if (rule.size() == 2) {
        continue;
      } else {
        if (IsTerminal(rule[0])) {
          continue;
        }
        bool has_found = false;
        char symb = rule[0];
        std::string final_symb;
        is_unary[conversion.first].emplace_back(rule, true);
        while (!has_found) {
          int counter = 0;
          for (auto& another_rule : base_form_[symb]) {
            if (another_rule.size() != 2) {
              if (IsTerminal(another_rule[0])) {
                final_symb = another_rule;
                has_found = true;
              }
              is_unary[symb].emplace_back(another_rule, true);
              symb = another_rule[0];
              break;
            }
          }
        }
        chomsky_form_[conversion.first].push_back(final_symb);
      }
    }
  }
  for (auto& conversion : base_form_) {
    for (auto& rule : conversion.second) {
      bool has_found = false;
      for (auto& is_un : is_unary[conversion.first]) {
        if (rule == is_un.first) {
          has_found = true;
          break;
        }
      }
      if (!has_found) {
        chomsky_form_[conversion.first].push_back(rule);
      }
    }
  }
}