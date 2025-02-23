#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <array>

class TrieNode {
public:
    std::array<std::unique_ptr<TrieNode>, 26> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

class Autocomplete {
public:
    Autocomplete();
    void loadDataset(const std::string& filename);
    std::vector<std::string> getSuggestions(const std::string& prefix);

private:
    std::unique_ptr<TrieNode> root;
    void insert(const std::string& word);
    void search(TrieNode* node, std::string prefix, std::vector<std::string>& suggestions);
};

#endif // AUTOCOMPLETE_H
