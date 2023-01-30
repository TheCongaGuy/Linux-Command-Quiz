#include "Test.hpp"

// Method runs all test methods, returning false if tests fail
// Takes an int reference that will be assigned an error code
bool testProgram(int& errorCode)
{
    if (!linkedListSetup())
        errorCode = -1;
    
    if (!linkedListAppend())
        errorCode = -2;

    if (!linkedListRemove())
        errorCode = -3;
    
    if (!dataSetup())
        errorCode = -4;
    
    if (!dataEdit())
        errorCode = -5;

    if (!dataStreamExtract())
        errorCode = -6;
    
    if (!dataListSetup())
        errorCode = -7;

    if (!dataListAppend())
        errorCode = -8;
    
    if (!dataListRemove())
        errorCode = -9;

    return errorCode == 0;
}

// Test Method checks to see if LinkedList was instantiated
bool linkedListSetup()
{
    LinkedList<int> testList;
    return testList.isEmpty();
}

// Test Method checks to see if nodes were added to the heap
bool linkedListAppend()
{
    // Instantiate a new list
    LinkedList<int> testList;

    // Add 1 to the list and check for it's existance
    testList.insertBack(1);
    if (testList.isEmpty())
        return false;
    if (testList.getData(0) != 1)
        return false;
    
    // Add 2 to the list and check for both nodes
    testList.insertBack(2);
    if (testList.isEmpty())
        return false;
    if (testList.getData(0) != 1)
        return false;
    if (testList.getData(1) != 2)
        return false;
    
    // Return true if all checks passed
    return true;
}

// Test Method checks to see if deletion works properly
bool linkedListRemove()
{
    // Set up test list
    LinkedList<int> testList;
    testList.insertBack(1);
    testList.insertBack(2);
    testList.insertBack(3);

    // Remove middle node
    if (!testList.removeAt(1))
        return false;
    if (testList.getData(1) != 3 || testList.getData(0) != 1)
        return false;
    
    // Attempt to remove a node outside the bounds
    if (testList.removeAt(2))
        return false;
    
    testList.insertBack(4);

    // Remove the end node
    if (!testList.removeAt(2))
        return false;
    if (testList.getData(1) != 3 || testList.getData(0) != 1)
        return false;
    
    // Remove head node
    if (!testList.removeAt(0))
        return false;
    if (testList.getData(0) != 3)
        return false;
    
    // Remove the only node in the list
    if (!testList.removeAt(0))
        return false;
    if (!testList.isEmpty())
        return false;
    
    // Return true if all checks passed
    return true;
}

// Test Method instantiates an empty data object
bool dataSetup()
{
    // Instantiate a default data object
    Data testData;
    if (testData.getComName() != "N/A")
        return false;
    if (testData.getComDesc() != "No Command Found")
        return false;
    if (testData.getComScore() != 0)
        return false;
    
    // Instantiate filled data
    Data filledData("g++", "Linux Compiler", 1);
    if (filledData.getComName() != "g++")
        return false;
    if (filledData.getComDesc() != "Linux Compiler")
        return false;
    if (filledData.getComScore() != 1)
        return false;
    
    return true;
}

// Test Method checks to see if data can me modified
bool dataEdit()
{
    // Instantiate a new data object
    Data testData;

    // Change each value in data
    testData.setComName("Test");
    if (testData.getComName() != "Test")
        return false;
    if (testData.getComDesc() != "No Command Found")
        return false;
    if (testData.getComScore() != 0)
        return false;
    
    testData.setComDesc("Hi");
    if (testData.getComName() != "Test")
        return false;
    if (testData.getComDesc() != "Hi")
        return false;
    if (testData.getComScore() != 0)
        return false;
    
    testData.setComScore(2);
    if (testData.getComName() != "Test")
        return false;
    if (testData.getComDesc() != "Hi")
        return false;
    if (testData.getComScore() != 2)
        return false;
    
    return true;
}

// Test Method checks to see if data can be extracted from a file
bool dataStreamExtract()
{
    // Instantiate a new data object
    Data testData;

    // Grab strings to compare
    std::string trueName, trueDesc, trueStrScore;
    int trueScore;
    std::ifstream file("commands.csv");
    std::getline(file, trueName,',');
    std::getline(file, trueDesc, ',');
    std::getline(file, trueStrScore,'\n');

    // Convert the score for comparison
    trueScore = std::stoi(trueStrScore);

    // Close then reopen the stream
    file.close();
    file.open("commands.csv");

    // Fill testData with info from the stream
    file >> testData;

    // Close the stream again
    file.close();

    // Compare the results
    if (trueName != testData.getComName())
        return false;
    if (trueDesc != testData.getComDesc())
        return false;
    if (trueScore != testData.getComScore())
        return false;
    
    return true;
}

// Following three methods test cooperation between data class and linked lists
bool dataListSetup()
{
    LinkedList<Data> testList;
    return testList.isEmpty();
}
bool dataListAppend()
{
    // Instantiate a new list
    LinkedList<Data> testList;

    // Add Data to the list and check for it's existance
    Data testData1;
    testList.insertBack(testData1);
    if (testList.isEmpty())
        return false;
    if (testList.getData(0).getComDesc() != testData1.getComDesc())
        return false;
    if (testList.getData(0).getComName() != testData1.getComName())
        return false;
    if (testList.getData(0).getComScore() != testData1.getComScore())
        return false;
    
    // Add Data to the list and check for both nodes
    Data testData2("Test", "This is a test for linked lists", 2);
    testList.insertBack(testData2);
    if (testList.isEmpty())
        return false;
    if (testList.getData(0).getComDesc() != testData1.getComDesc())
        return false;
    if (testList.getData(0).getComName() != testData1.getComName())
        return false;
    if (testList.getData(0).getComScore() != testData1.getComScore())
        return false;
        
    if (testList.getData(1).getComDesc() != testData2.getComDesc())
        return false;
    if (testList.getData(1).getComName() != testData2.getComName())
        return false;
    if (testList.getData(1).getComScore() != testData2.getComScore())
        return false;
    
    // Return true if all checks passed
    return true;
}
bool dataListRemove()
{

    // Set up test list
    LinkedList<Data> testList;
    Data test1,
         test2("Test", "This is a test", 2),
         test3("Real", "This is NOT a test", 3),
         test4("Fake", "I am lying", 4);
    
    testList.insertBack(test1);
    testList.insertBack(test2);
    testList.insertBack(test3);

    // Remove middle node
    if (!testList.removeAt(1))
        return false;
    if (testList.getData(1).getComScore() != 3 || testList.getData(0).getComScore() != 0)
        return false;
    
    // Attempt to remove a node outside the bounds
    if (testList.removeAt(2))
        return false;
    
    testList.insertBack(test4);

    // Remove the end node
    if (!testList.removeAt(2))
        return false;
    if (testList.getData(1).getComScore() != 3 || testList.getData(0).getComScore() != 0)
        return false;
    
    // Remove head node
    if (!testList.removeAt(0))
        return false;
    if (testList.getData(0).getComScore() != 3)
        return false;
    
    // Remove the only node in the list
    if (!testList.removeAt(0))
        return false;
    if (!testList.isEmpty())
        return false;
    
    // Return true if all checks passed
    return true;
}