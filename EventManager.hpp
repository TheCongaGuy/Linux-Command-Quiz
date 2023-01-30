#pragma once

#include "Profile.hpp"
#include "LinkedList.hpp"
#include "Data.hpp"
#include <fstream>
#include <cstdlib>

// Global variables for the game
extern LinkedList<Data> commands;
extern profile profiles[11];
extern int totalFileIndex, currentPlayer;

// Obtains the user's choice from a menu
// Returns a bool and assigns an int to the user's choice
bool displayMenu(int& choice);

// Prints the rules to the terminal
void displayRules();

// Find a user's profile, or create one
void getUserDetails();

// Run the game
void playGame();

// Add a command to the linked list of commands
void addCommand();

// Remove a command from the linked list of commands
void remCommand();

// Display all commands from the linked list
void dispCommands();

// Saves all data into their respective csv files
void saveAll();