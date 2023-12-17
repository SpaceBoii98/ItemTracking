#ifndef TEXTANALYZER_H
#define TEXTANALYZER_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

class TextAnalyzer {

public:
    // Constructor to read the input file
    TextAnalyzer(const std::string& fileName);

    // Function to calculate the frequency of a specific item
    int calculateFrequency(const std::string& item) const;

    // Function to print the frequency of all items
    void printAllFrequencies() const;

    // Function to print a histogram of item frequencies
    void printHistogram() const;

    //Function to write data to frequency.dat file
    void writeToFile(const std::string& filename) const;

private:
    // Function to read the input file and return a list of items
    std::vector<std::string> readInputFile(const std::string& fileName) const;

    std::vector<std::string> itemsList;
    std::unordered_map<std::string, int> frequencyMap;
};

#endif // TEXTANALYZER_H
