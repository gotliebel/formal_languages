#include "LengthInLanguage.h"
#include <numeric>

std::unordered_set<int> CheckLength::StarKleene(const std::unordered_set<int>& us, const int& l, const int& k) {
  std::unordered_set<int> unordered_set;
  int gcd = *us.begin();
  for (auto& i : us) {
    gcd = std::gcd(i, gcd);
  }
  int vichet = 0;
  while (unordered_set.find((vichet * gcd) % k) == unordered_set.end()) {
    unordered_set.insert((vichet * gcd) % k);
    vichet++;
  }
  return unordered_set;
}

std::unordered_set<int> CheckLength::Concatenation(const std::unordered_set<int>& us1,
                                                   const std::unordered_set<int>& us2,
                                                   const int& k) {
  std::unordered_set<int> us;
  for (auto& i : us1) {
    for (auto& j : us2) {
      us.insert((i + j) % k);
    }
  }
  return us;
}

bool CheckLength::Parse(const std::string& str, const int& l, const int& k) {
  bool is_in_language = false;
  std::stack<std::unordered_set<int>> stack;
  for (char i : str) {
    if (isalpha(i)) {
      stack.push(std::unordered_set<int>{1});
    } else if (i == '.') {
      auto top_element = stack.top();
      stack.pop();
      auto second_top_element = stack.top();
      stack.pop();
      stack.push(CheckLength::Concatenation(top_element, second_top_element, k));
    } else if (i == '+') {
      auto top_element = stack.top();
      stack.pop();
      auto second_top_element = stack.top();
      stack.pop();
      top_element.insert(second_top_element.begin(), second_top_element.end());
      stack.push(top_element);
    } else if (i == '*') {
      auto top_element = stack.top();
      stack.pop();
      stack.push(StarKleene(top_element, l, k));
    }
  }
  for (auto& i : stack.top()) {
    if (i == l) {
      is_in_language = true;
      break;
    }
  }
  return is_in_language;
}

bool CheckLength::CheckIsInLanguage(const std::string& string, const int& l, const int& k) {
  return Parse(string, l, k);
}