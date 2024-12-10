#include <iostream>
#include <string>
#include <cctype>

treeNode* parseE(const std::string& input, size_t& pos);
treeNode* parseT(const std::string& input, size_t& pos);
treeNode* parseP(const std::string& input, size_t& pos);
treeNode* parseF(const std::string& input, size_t& pos);
