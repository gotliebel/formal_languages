#pragma once

#include <stack>
#include <string>
#include <vector>
#include <unordered_set>

namespace CheckLength {
bool Parse(const std::string& str, const int& l, const int& k);
bool CheckIsInLanguage(const std::string& string, const int& l, const int& k);
std::unordered_set<int> StarKleene(const std::unordered_set<int>& us, const int& l, const int& k);
std::unordered_set<int> Concatenation(const std::unordered_set<int>& us1,
                                      const std::unordered_set<int>& us2,
                                      const int& k);
}