#pragma once
#include "convert_to_chomsky.h"

class CockeYoungerKasami {
 public:
  void SetForm(const std::unordered_map<char, std::vector<std::string>>&);
  bool IsInLanguage(const std::string&);
 private:
  std::unordered_map<char, std::vector<std::string>> chomsky_form_;
  std::unordered_map<char, std::vector<std::vector<bool>>> dp_;
};