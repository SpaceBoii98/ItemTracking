#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "TextAnalyzer.h"
#include <limits>

// Constructor to read the input file
TextAnalyzer::TextAnalyzer(const std::string& fileName) {
    itemsList = readInputFile(fileName);

    // Initialize frequency map
    for (const std::string& item : itemsList) {
        frequencyMap[item] = 0;
    }
}

// Function to calculate the frequency of a specific item
int TextAnalyzer::calculateFrequency(const std::string& item) const {
    int frequency = 0;

    // singular and plural forms
    for (const std::string& i : itemsList) {
        if (i == item || i + "s" == item || i == item + "s") {
            frequency++;
        }
    }


    return frequency;
}

// Function to print the frequency of all items
void TextAnalyzer::printAllFrequencies() const {
    std::unordered_map<std::string, int> frequencyMap;

    for (const std::string& item : itemsList) {
        frequencyMap[item]++;
    }

    for (const auto& entry : frequencyMap) {
        std::cout << entry.first << " " << entry.second << std::endl;
    }
}

// Function to print a histogram of item frequencies
void TextAnalyzer::printHistogram() const {
    std::unordered_map<std::string, int> frequencyMap;

    for (const std::string& item : itemsList) {
        frequencyMap[item]++;
    }

    for (const auto& entry : frequencyMap) {
        std::cout << entry.first << " ";
        for (int i = 0; i < entry.second; ++i) {
            std::cout << '*';
        }
        std::cout << std::endl;
    }
}

//Function for writing data to frequency.data file 
void TextAnalyzer::writeToFile(const std::string& fileName) const {
    std::ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << fileName << std::endl;
        return;
    }

    for (const auto& entry : frequencyMap) {
        outputFile << entry.first << " " << entry.second << std::endl;
    }

    outputFile.close();
}


// Function to read the input file and return a list of items
std::vector<std::string> TextAnalyzer::readInputFile(const std::string& fileName) const {
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> items;
    std::string item;

    while (inputFile >> item) {
        items.push_back(item);
    }

    inputFile.close();
    return items;
}

int getChoice() {
    int choice;
    std::cout << "Enter your choice (1-4): ";

    while (true) {
        std::cin >> choice;

        if (std::cin.fail()) {
            // If the input is not a valid integer
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            std::cout << "Invalid choice. Please choose one of the options above. ";
        }
        else {
            // Input is a valid integer
            break;
        }
    }

    return choice;
}

//Main function
int main() {
    const std::string fileName = "CS210_Project_Three_Input_File.txt";
    TextAnalyzer textAnalyzer(fileName);

    while (true) {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Find frequency of a specific item" << std::endl;
        std::cout << "2. Find frequency of all items" << std::endl;
        std::cout << "3. Print histogram" << std::endl;
        std::cout << "4. Exit" << std::endl;

        int choice = getChoice();

        switch (choice) {
        case 1: {
            std::string searchItem;
            std::cout << "Enter the item to look for: ";
            std::cin >> searchItem;
            int frequency = textAnalyzer.calculateFrequency(searchItem);
            std::cout << "The frequency of " << searchItem << " is: " << frequency << std::endl;
            break;
        }
        case 2:
            textAnalyzer.printAllFrequencies();
            break;
        case 3:
            textAnalyzer.printHistogram();
            break;
        case 4:
            textAnalyzer.writeToFile("frequency.dat");
            std::cout << "Data written to frequency.dat. Exiting the program. Goodbye!" << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please choose one of the options above." << std::endl;
        }
    }

    return 0;
}