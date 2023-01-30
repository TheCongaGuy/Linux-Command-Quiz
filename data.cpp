#include "Data.hpp"

// Default Constructor
Data::Data(std::string name, std::string desc, int scr)
{
    commandName = name;
    commandDescription = desc;
    score = scr;
}

// Getters
std::string Data::getComName() const { return commandName; }
std::string Data::getComDesc() const { return commandDescription; }
int Data::getComScore() const { return score; }
// Setters
void Data::setComName(const std::string name) { commandName = name; }
void Data::setComDesc(const std::string desc) { commandDescription = desc; }
void Data::setComScore(const int scr) { score = scr; }

// Operator Extraction Overload
std::istream& operator>>(std::istream& lhs, Data& rhs)
{
    // Catches data from the stream
    std::string name, desc, score;
    int numScore;

    // Grab the values from the stream
    std::getline(lhs, name, ',');
    std::getline(lhs, desc, ',');
    std::getline(lhs, score, '\n');
    
    // Convert the score from a string to an int
    numScore = std::stoi(score);

    // Assign the values to the Data class
    rhs.setComName(name);
    rhs.setComDesc(desc);
    rhs.setComScore(numScore);

    return lhs;
}