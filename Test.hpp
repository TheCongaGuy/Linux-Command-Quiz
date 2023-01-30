#pragma once

#include "LinkedList.hpp"
#include "Data.hpp"
#include <fstream>

// Method runs all test methods, returning false if tests fail
// Takes an int reference that will be assigned an error code
bool testProgram(int& errorCode);

// Test methods for linked list
bool linkedListSetup();
bool linkedListAppend();
bool linkedListRemove();

// Test methods for Data class
bool dataSetup();
bool dataEdit();
bool dataStreamExtract();

// Test methods for linked data lists
bool dataListSetup();
bool dataListAppend();
bool dataListRemove();