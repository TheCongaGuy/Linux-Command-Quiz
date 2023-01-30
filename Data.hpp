#pragma once

#include <iostream>
#include <fstream>

// Class to store the data from the CSV file
class Data
{
public:
    // Default Constructor
    Data(std::string name = "N/A", std::string desc = "No Command Found", int scr = 0);

    // Getters
    std::string getComName() const;
    std::string getComDesc() const;
    int getComScore() const;
    // Setters
    void setComName(const std::string name);
    void setComDesc(const std::string desc);
    void setComScore(const int scr);

private:
    std::string commandName;
    std::string commandDescription;

    int score;
};

// Stream Extraction Overload
std::istream& operator>>(std::istream& lhs, Data& rhs);