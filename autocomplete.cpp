#include "autocomplete.h"
#include <fstream>
#include <algorithm>

Autocomplete::Autocomplete() : root(std::make_unique<TrieNode>()) {}

void Autocomplete::insert(const std::string& word) {
    TrieNode* node = root.get();
    for (char ch : word) {
        if (!isalpha(ch)) continue;
        int index = tolower(ch) - 'a';
        if (!node->children[index]) {
            node->children[index] = std::make_unique<TrieNode>();
        }
        node = node->children[index].get();
    }
    node->isEndOfWord = true;
}

void Autocomplete::loadDataset(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return;
    }
    std::string word;
    while (file >> word) {
        insert(word);
    }
}

void Autocomplete::search(TrieNode* node, std::string prefix, std::vector<std::string>& suggestions) {
    if (node->isEndOfWord) {
        suggestions.push_back(prefix);
    }
    for (int i = 0; i < 26; ++i) {
        if (node->children[i]) {
            search(node->children[i].get(), prefix + static_cast<char>('a' + i), suggestions);
        }
    }
}

std::vector<std::string> Autocomplete::getSuggestions(const std::string& prefix) {
    TrieNode* node = root.get();
    for (char ch : prefix) {
        if (!isalpha(ch)) return {};
        int index = tolower(ch) - 'a';
        if (!node->children[index]) {
            return {};
        }
        node = node->children[index].get();
    }
    std::vector<std::string> suggestions;
    search(node, prefix, suggestions);
    return suggestions;
}
