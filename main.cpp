#include "autocomplete.h"
#include <iostream>

int main() {
    Autocomplete autocomplete;
    autocomplete.loadDataset("dataset.txt");
    
    std::string prefix;
    while (true) {
        std::cout << "Enter a prefix (or type 'exit' to quit): ";
        std::cin >> prefix;
        
        if (prefix == "exit") break;
        
        std::vector<std::string> suggestions = autocomplete.getSuggestions(prefix);
        
        std::cout << "Suggestions: " << std::endl;
        for (const auto& word : suggestions) {
            std::cout << word << std::endl;
        }
    }
    
    return 0;
}
