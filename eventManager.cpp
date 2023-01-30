#include "EventManager.hpp"

// Obtains the user's choice from a menu
// Returns false when user quits and assigns the user's choice to the passed in int
bool displayMenu(int& choice)
{
    // Obtain user input, looping while input is invalid
    do
    {
        std::cout << "--------------------------------------------------------------------------" << std::endl
                  << "[User: " << profiles[currentPlayer].userName << " | " << profiles[currentPlayer].userScore << " pts]" << std::endl
                  << "Please select from the options below:" << std::endl
                  << "1. Game Rules" << std::endl
                  << "2. New Game" << std::endl
                  << "3. Load Game" << std::endl
                  << "4. Add Command" << std::endl
                  << "5. Remove Command" << std::endl
                  << "6. Display Commands" << std::endl
                  << "7. Save & Quit" << std::endl;
        
        // Obtain and verify user input
        std::cin >> choice;

        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(INT64_MAX, '\n');
        }
    } while (choice < 1 || choice > 7);
    
    // Returns true if user chooses not to quit
    return choice != 7;
}

// Prints the rules to the terminal
void displayRules()
{
    std::cout << "--------------------------------------------------------------------------------" << std::endl
              << "The objective of the game is to match Linux commands to appropriate descriptions" << std::endl
              << "of those commands. If a command is matched, then you earn the points for" << std::endl
              << "that command. The if the command is not matched, then you lose that many" << std::endl
              << "points. Yes, negative point totals are possible." << std::endl << std::endl 
 
              << "Before the game, you select the number of match questions to be asked." << std::endl
              << "The game continues until the number is reached." << std::endl
              << "(Press Enter to return to menu)" << std::endl;

    // Wait for user to press enter
    std::cin.ignore(INT64_MAX, '\n'); // Eats previous enter press
    std::cin.get();
}

// Find a user's profile, or create one
void getUserDetails()
{
    // Catches user input
    std::string name, confirmation;

    std::cout << "--------------------------------------------------------------------------" << std::endl
              << "Please Enter your Name" << std::endl;
    
    std::cin.ignore(INT64_MAX, '\n'); // Eats previous enter press
    std::getline(std::cin, name);

    // Check if this player exists
    for (int i = 0; i < totalFileIndex; i++)
        // Load the player if found
        if (profiles[i].userName == name)
        {
            std::cout << "Player Found!" << std::endl;
            currentPlayer = i;
            return;
        }
    
    // If no entry exists, check if space is available for a new player
    if (totalFileIndex < 10)
    {
        std::cout << "Creating Profile..." << std::endl;
        profiles[currentPlayer].userName = name;
        totalFileIndex++;
        return;
    }

    // If no space is available, warn of an override and check for confirmation
    std::cout << "Not Enough Space..." << std::endl
                << "Creating a new profile will override player: " << profiles[--currentPlayer].userName << std::endl
                << "Do you wish to continue? (y/n)" << std::endl;
    
    std::getline(std::cin, confirmation);

    // Override iff user selects yes
    if (confirmation[0] == 'y')
    {
        profiles[currentPlayer].userName = name;
        profiles[currentPlayer].userScore = 0;
        return;
    }

    // If load fails, try again
    getUserDetails();
}

// Run the game
void playGame()
{
    // Random number generator
    srand(time(NULL));

    // Catches user input
    int input;
    // Records the correct answer's location
    int correctIndex;
    // Controlls the number of questions
    int numQuestions = 0;
    // Holds size of the linked list for later use
    int listSize = commands.size();

    // Get how many questions the player would like to be asked
    std::cout << "--------------------------------------------------------------------------" << std::endl
              << "How many questions would you like? (5 - 30)" << std::endl;
    
    do
    {
        std::cin >> input;
        std::cin.clear();
        std::cin.ignore(INT64_MAX, '\n');
    } while (std::cin.fail());

    // Restrict input between the range 5 to 30
    if (input < 5)
        numQuestions = 5;
    else if (input > 30)
        numQuestions = 30;
    else
        numQuestions = input;

    // Generate random questions for the specified number of questions
    for (int i = 0; i < numQuestions; i++)
    {
        // Generate the correct and incorrect data
        Data correct = commands.getData(rand() % listSize);
        Data incorrect1 = commands.getData(rand() % listSize);
        Data incorrect2 = commands.getData(rand() % listSize);

        // Ensure that there are not two copies of answers
        while (correct.getComDesc() == incorrect1.getComDesc())
            incorrect1 = commands.getData(rand() % listSize);
        while (correct.getComDesc() == incorrect2.getComDesc())
            incorrect2 = commands.getData(rand() % listSize);

        std::cout << "--------------------------------------------------------------------------" << std::endl
                  << "Please pick the correct description for the following command: " << correct.getComName() << std::endl
                  << "--------------------------------------------------------------------------" << std::endl
                  << "[User: " << profiles[currentPlayer].userName << " | " << profiles[currentPlayer].userScore << " pts]" << std::endl;

        // Generate random locations for the description
        switch (rand() % 3)
        {
            case 0:
                correctIndex = 1;
                std::cout << "1. " << correct.getComDesc() << " (" << correct.getComScore() << " pts)" << std::endl
                          << "2. " << incorrect1.getComDesc() << " (" << incorrect1.getComScore() << " pts)" << std::endl
                          << "3. " << incorrect2.getComDesc() << " (" << incorrect2.getComScore() << " pts)" << std::endl;
                break;
            
            case 1:
                correctIndex = 2;
                std::cout << "1. " << incorrect1.getComDesc() << " (" << incorrect1.getComScore() << " pts)" << std::endl
                          << "2. " << correct.getComDesc() << " (" << correct.getComScore() << " pts)" << std::endl
                          << "3. " << incorrect2.getComDesc() << " (" << incorrect2.getComScore() << " pts)" << std::endl;
                break;
            
            case 2:
                correctIndex = 3;
                std::cout << "1. " << incorrect1.getComDesc() << " (" << incorrect1.getComScore() << " pts)" << std::endl
                          << "2. " << incorrect2.getComDesc() << " (" << incorrect2.getComScore() << " pts)" << std::endl
                          << "3. " << correct.getComDesc() << " (" << correct.getComScore() << " pts)" << std::endl;
                break;
        }

        // Get user input
        do
        {
            std::cin >> input;
            std::cin.clear();
            std::cin.ignore(INT64_MAX, '\n');
        } while (std::cin.fail());

        // Update the user's score
        if (input == correctIndex)
            profiles[currentPlayer].userScore += correct.getComScore();
        else
            profiles[currentPlayer].userScore -= correct.getComScore();
    }
}

// Add a command to the linked list
void addCommand()
{
    // Catches user input
    std::string newName, newDesc, newScore;
    // Stores size of the list for future reference
    int listSize = commands.size();

    // Get information on the new command
    std::cout << "--------------------------------------------------------------------------" << std::endl
              << "What is the name of this command?" << std::endl;
    
    std::cin.ignore(INT64_MAX, '\n'); // Eats previous enter press
    std::getline(std::cin, newName);

    // Check if command exists
    for (int i = 0; i < listSize; i++)
        if (newName == commands.getData(i).getComName())
            {
                std::cout << "This command already exists! If you would like to redefine it," << std::endl
                          << "please delete it first!" << std::endl;
                return;
            }

    std::cout << "--------------------------------------------------------------------------" << std::endl
              << "What does " << newName << " do?" << std::endl;
    
    std::getline(std::cin, newDesc);

    std::cout << "--------------------------------------------------------------------------" << std::endl
              << "And what score would you like to give this command?" << std::endl;
    
    std::getline(std::cin, newScore);

    // Create a new data object
    Data newCommand(newName, '\"' + newDesc + '\"', stoi(newScore));

    // Append the new command to the list
    commands.insertBack(newCommand);
}

void remCommand()
{
    // Catches user input
    std::string name;

    // Stores size of the list for future reference
    int listSize = commands.size();

    // Get the name of the target command
    std::cout << "--------------------------------------------------------------------------" << std::endl
              << "What command do you wish to delete?" << std::endl;
    
    std::cin.ignore(INT64_MAX, '\n'); // Eats previous enter press
    std::getline(std::cin, name);

    // Search for the index of the command
    for (int i = 0; i < listSize; i++)
        if (name == commands.getData(i).getComName())
            {
                commands.removeAt(i);
                return;
            }

    // Alert the user if the command was not found
    std::cout << "This command was not found! Did you spell it correctly?" << std::endl;
}

// Display all commands in the list
void dispCommands()
{
    // Create a divider to make reading easier
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    // Stores size of the list for future reference
    int listSize = commands.size();

    // Iterate through each element in the list and print them
    for (int i = 0; i < listSize; i++)
        std::cout << i + 1 << ". " << commands.getData(i).getComName() << " - "
                  << commands.getData(i).getComDesc() << " (" << commands.getData(i).getComScore() << " pts)" << std::endl;
}

// Saves all data into their respective csv files
void saveAll()
{
    // Stores size of the list for future reference
    int listSize = commands.size();

    // File containing data for the linked list
    std::fstream commandFile("commands.csv");
    // File containing data for the users
    std::fstream userFile("profiles.csv");

    // Save the list to the commands.csv file
    for (int i = 0; i < listSize; i++)
    {
        commandFile << commands.getData(i).getComName() << ',' 
                    << commands.getData(i).getComDesc() << ',' 
                    << commands.getData(i).getComScore();
        
        // Add a new line if more commands need to be added
        if (i != listSize - 1)
            commandFile << '\n';
    }
    // Close the command file
    commandFile.close();
    
    // Save the profiles to the profiles.csv file backwards to preserve the order
    for (int i = totalFileIndex - 1; i >= 0; i--)
    {
        userFile << profiles[i].userName << ',' << profiles[i].userScore;

        // Add a new line if more commands need to be added
        if (i != 0)
            userFile << '\n';
    }
    // Close the user file
    userFile.close();
}