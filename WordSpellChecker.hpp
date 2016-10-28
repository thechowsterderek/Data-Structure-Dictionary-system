
#ifndef WORDCHECKER_HPP
#define WORDCHECKER_HPP

#include <string>
#include <vector>
#include "Set.hpp"



class WordChecker
{
public:
    // The constructor requires a Set of words to be passed into it.  The
    // WordChecker will store a reference to a const Set, which it will use
    // whenever it needs to look up a word.
    WordChecker(const Set<std::string>& words);


    // wordExists() returns true if the given word is spelled correctly,
    // false otherwise.
    bool wordExists(const std::string& word) const;


    // findSuggestions() returns a vector containing suggested alternative
    // spellings for the given word, using the five algorithms described in
    // the project write-up.
    std::vector<std::string> findSuggestions(const std::string& word) const;

    std::vector<std::string> vCombiner(const std::vector<std::string> first,std::vector<std::string> second) const;

    std::vector<std::string> swapping(const std::string& word)const;

    std::vector<std::string> adder(const std::string& word)const;

    std::vector<std::string> deleter(const std::string& word)const;

    std::vector<std::string> replacer(const std::string& word)const;

    std::vector<std::string> splitter(const std::string& word)const;
private:
    const Set<std::string>& words;
};



#endif // WORDCHECKER_HPP

