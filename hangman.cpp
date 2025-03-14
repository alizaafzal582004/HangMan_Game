#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

// Structure to represent a node in the linked list
struct WordNode {
    string word;          // The word stored in the node
    WordNode* next;       // Pointer to the next node
};

// Function to add a word to the linked list
void addWord(WordNode*& head, const string& word) {
    WordNode* newNode = new WordNode; // Create a new node
    newNode->word = word;              // Set the word
    newNode->next = head;              // Point to the current head
    head = newNode;                    // Update head to the new node
}

// Function to clear the linked list and free memory
void clearWords(WordNode* head) {
    while (head) {
        WordNode* temp = head; // Temporary pointer to hold the current node
        head = head->next;     // Move to the next node
        delete temp;           // Free the memory of the current node
    }
}

// Function to display the main menu
void displayMenu(int numTries, const string& hiddenWord, const string& message) {
    cout << "\033[35m"; // Set text color to magenta
    cout << "\033[2J";  // Clear screen
    cout << "\033[H";   // Move cursor to top-left corner
    cout << "\t\t\t************************************\n";
    cout << "\t\t\t*                                  *\n";
    cout << "\t\t\t*          SAVE THE MAN            *\n";
    cout << "\t\t\t*                                  *\n";
    cout << "\t\t\t************************************\n";

    cout << " \t\t 0 " << endl;
    cout << " \t\t/|\\" << endl;
    cout << " \t\t/ \\" << endl;

    cout << "\t\t==========================================\n";
    cout << "\n\t\tYou have " << numTries << " tries to guess the word.";
    cout << "\n\n\t\t\t\t" << message << "\n";
    cout << "\t\t==========================================\n";
    cout << "\033[0m"; // Reset text color
}

// Function to check the guessed letter
int checkGuess(const string& secretWord, string& hiddenWord, char guess) {
    int matches = 0;
    for (size_t i = 0; i < secretWord.length(); i++) {
        if (guess == hiddenWord[i]) {
            return 0; // Letter already guessed
        }
        if (guess == secretWord[i]) {
            hiddenWord[i] = guess; // Update hidden word
            matches++;
        }
    }
    return matches; // Return number of matches
}

// Function to save the results to a file
void saveResultsToFile(const string& category, const string& secretWord, bool isWin) {
    ofstream resultFile("Result.hangman.txt", ios::app); // Open file in append mode
    if (!resultFile.is_open()) {
        cerr << "Error: Unable to open file Result.hangman.txt" << endl;
        return;
    }

    resultFile << "Category: " << category << "\n";
    resultFile << "Secret Word: " << secretWord << "\n";
    resultFile << "Result: " << (isWin ? "Win" : "Loss") << "\n";
    resultFile << "-----------------------------------\n";
    resultFile.close();
}

// Function to play the game
void playGame(const string& secretWord, const string& category, bool isEasyLevel) {
    int numTries = 3; // Number of tries
    string hiddenWord(secretWord.length(), '-'); // Initialize hidden word
    string message = "Play!";
    char letter;
    bool isWin = false;

    // Reveal the first letter for easy level
    if (isEasyLevel) {
        hiddenWord[0] = secretWord[0];
    }

    while (numTries > 0) {
        displayMenu(numTries, hiddenWord, message);
        cout << "\n\t\t\t\t" << hiddenWord;
        cout << "\n\n\t\t\t\tGuess a letter: ";
        cin >> letter;

        if (checkGuess(secretWord, hiddenWord, letter) == 0) {
            message = "Incorrect letter.";
            numTries--;
        } else {
            message = "NICE! You guessed a letter.";
        }

        if (secretWord == hiddenWord) {
            message = "Congratulations! You got it. Man has been saved!";
            isWin = true;
            displayMenu(numTries, hiddenWord, message);
            cout << "\\ 0 / " << endl;
            cout << "  |" << endl;
            cout << " / \\" << endl;
            cout << "\t\t==========================================\n";
            cout << "\n\t\t\tThe word is : " << secretWord << endl;
            cout << "\t\t\t\t                                      \n";
            cout << "\t\t==========================================\n";
            break;
        }
    }

    if (numTries == 0) {
        message = "NOOOOOOO!...Man has been hanged.";
        displayMenu(numTries, hiddenWord, message);
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |    /|\\" << endl;
        cout << "  |    / \\" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "__|___ " << endl;
        cout << "\t\t==========================================\n";
        cout << "\n\t\t\tThe word was : " << secretWord << endl;
        cout << "\t\t\t\t                                  \n";
        cout << "\t\t==========================================\n";
    }

    saveResultsToFile(category, secretWord, isWin); // Save the result to file
}

// Function to get a random word from the linked list
string getRandomWord(WordNode* head) {
    int count = 0;
    WordNode* current = head;

    // Count the number of words in the linked list
    while (current) {
        count++;
        current = current->next;
    }

    if (count == 0) return ""; // Return empty string if no words

    // Generate a random index
    int randomIndex = rand() % count;
    current = head;

    // Traverse to the random index
    for (int i = 0; i < randomIndex; i++) {
        current = current->next;
    }

    return current->word; // Return the word at the random index
}

int main() {
    int category;
    WordNode* words = nullptr; // Head of the linked list

    // Add words to the linked list based on categories
    string months[12] = {
        "january", "february", "march", "april", "may", "june", 
        "july", "august", "september", "october", "november", "december"
    };
    string fruits[20] = {
        "apple", "banana", "cherry", "date", "elderberry", "fig", "grape",
        "honeydew", "kiwi", "lemon", "mango", "nectarine", "orange",
        "papaya", "quince", "raspberry", "strawberry", "tangerine",
        "blueberry", "watermelon"
    };
    string animals[20] = {
        "antelope", "buffalo", "cheetah", "dolphin", "elephant", "flamingo",
        "giraffe", "hippopotamus", "iguana", "jaguar", "kangaroo", "lemur",
        "mongoose", "narwhal", "octopus", "penguin", "quokka", "rhinoceros",
        "salamander", "tiger"
    };

    cout << "\t\t\t\t************************************\n";
    cout << "\t\t\t\t*                                  *\n";
    cout << "\t\t\t\t*      WELCOME TO HANGMAN GAME     *\n";
    cout << "\t\t\t\t*                                  *\n";
    cout << "\t\t\t\t************************************\n";
    cout << "\t\t\t\t                                  \n";
    cout << "\n\t\t\t*************************************************\n";

    cout << "\n\t\t\t\t      SELECT A CATEGORY: ";
    cout << "\t\t\t\t                                  \n";
    cout << "\n\t\t\t\t     1. MONTHS";
    cout << "\n\t\t\t\t     2. FRUITS ";
    cout << "\n\t\t\t\t     3. ANIMALS ";
    cout << "\t\t\t\t                                  \n";
    cout << "\n\t\t\t*************************************************\n";

    cout << "\n\t\t\t\t      Enter your choice: ";
    cin >> category;
    
    // Populate the linked list based on the selected category
    if (category == 1) {
        for (const auto& month : months) {
            addWord(words, month);
        }
    } else if (category == 2) {
        for (const auto& fruit : fruits) {
            addWord(words, fruit);
        }
    } else if (category == 3) {
        for (const auto& animal : animals) {
            addWord(words, animal);
        }
    } else {
        cout << "Invalid category. Defaulting to months.\n";
        for (const auto& month : months) {
            addWord(words, month);
        }
    }
    cout << "\033[2J";  // Clear screen
    cout << "\033[H";   // Move cursor to top-left corner
    cout << "\t\t\t\t************************************\n";
    cout << "\t\t\t\t*                                  *\n";
    cout << "\t\t\t\t*      Select Difficulty Level     *\n";
    cout << "\t\t\t\t*                                  *\n";
    cout << "\t\t\t\t************************************\n";
    cout << "\t\t\t\t                                  \n";
    cout << "\n\t\t\t*************************************************\n";
    cout << "\t\t\t\t                                  \n";
    cout << "\n\t\t\t\t1. Easy Level ";
    cout << "\n\t\t\t\t2. Hard Level ";
    cout << "\t\t\t\t                                  \n";
    cout << "\n\t\t\t*************************************************\n";
    cout << "\t\t\t\t                                  \n";
    cout << "\n\t\t\t\tEnter your choice: ";
    int level;
    cin >> level;
    bool isEasyLevel = (level == 1);

    srand(time(NULL)); // Seed random number generator
    string secretWord = getRandomWord(words); // Get a random word from the linked list

    if (secretWord.empty()) {
        cout << "No words available. Exiting game." << endl;
        clearWords(words); // Clean up the linked list
        return 0;
    }

    playGame(secretWord, (category == 1) ? "MONTHS" : (category == 2) ? "FRUITS" : "ANIMALS", isEasyLevel); // Start the game

    clearWords(words); // Clean up the linked list
    return 0;
}
