#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "linked_list.h"

// Reformatting words to a more efficient format
std::string cleanWord(std::string word) {
    std::string clean;
    for (char c : word) {
        if (std::isalnum(c)) {
            clean += std::tolower(c);
        }
    }
    return clean;
}

void tokenize(std::string filename, LinkedList<std::string>& list) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string rawWord;
    while (file >> rawWord) {
        std::string processed = cleanWord(rawWord);

        if (!processed.empty()) {
            list.insertBack(processed);
        }
    }
    file.close();
}

#endif 