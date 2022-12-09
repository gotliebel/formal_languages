#pragma once
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class Grammatica {
 public:
  void AddRule(const std::string& rule);
  std::unordered_map<char, std::vector<std::string>> GetChomskyForm() const;
  void ConvertToChomsky();
 private:
  void DeleteNonReachable();
  void DeleteMixed();
  void DeleteLong();
  void DeleteUnary();
  bool IsTerminal(char);
  bool IsNonTerminal(char);
  std::unordered_map<char, std::vector<std::string>> base_form_;
  std::unordered_map<char, std::vector<std::string>> chomsky_form_;
  std::set<char> terminal_;
  std::set<char> non_terminal_;
  std::string alphabet_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
};