#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

void printGreeting();
std::string selectSecretWord();
void printNumLettersInWord(std::string word, std::vector<char>& unguessedWord);
char getUserGuess();
bool checkOldGuesses(char userGuess, std::vector<char> allGuesses);
void updateSecretWordVector(std::vector<char>& secretWord, std::vector<int>& correctGuessIndex,
                            char userGuess);
void printIncorrectGuesses(std::vector<char> incorrectGuesses);

int main() {

    //Greet the user with a greeting function
    printGreeting();
    bool playGame = true;

    //Use a while loop to play the game continuously until the user quits at the end of the game
    while (playGame) {
        bool wordFullyGuessed = false;

        //Select a word from the wordbank using a function and assign the secret word to a string variable
        std::string word = selectSecretWord();

        //Indicate num letters in word using a function and use a vector to represent the word to the user
        std::vector<char> unguessedWord(word.size());
        printNumLettersInWord(word, unguessedWord);

        //Variables to track correct, incorrect, and total guesses
        int numCorrectGuesses = 0;
        int numIncorrectGuesses = 0;
        int totalGuesses;
        bool guessIsRight;

        //vectors to track how many times a correct letter appears in the word, what incorrect guesses the user
        //has made, and all guesses the user has made (to make sure they don't guess the same correct letter twice and
        //mess up the guess count).
        std::vector<int> correctGuessIndex;
        std::vector<char> incorrectGuesses;
        std::vector<char> allGuesses;

        //While loop to get another letter from the user as long as the word hasn't been fully guessed
        while (!wordFullyGuessed) {
            char userGuess = getUserGuess();
            //Check if letter has been guessed previously. If so, reprompt, else, determine if the guess is correct
            bool alreadyGuessed = checkOldGuesses(userGuess, allGuesses);
            if (alreadyGuessed) {
                std::cout << "Sorry, that character was already guessed. Try again." << std::endl;
                continue;
            }
            else {
                allGuesses.push_back(userGuess);
                for (unsigned int i = 0; i < word.size(); ++i) {
                    if (userGuess == word.at(i)) {
                        correctGuessIndex.push_back(i);
                    }
                }
                if (!correctGuessIndex.empty()) {
                    guessIsRight = true;
                }
                else {
                    guessIsRight = false;
                }

                //If the guess is correct, show the user an updated representation of the word, else give a list of
                //incorrect guesses.
                if (guessIsRight) {
                    std::cout << "You correctly guessed the letter " << userGuess << "!" << std::endl;
                    std::cout << "Here's the word with your correct guesses showing:" << std::endl;
                    updateSecretWordVector(unguessedWord, correctGuessIndex, userGuess);
                    for (char i : unguessedWord) {
                        std::cout << i;
                    }
                    std::cout << std::endl;
                    numCorrectGuesses++;
                }
                else {
                    std::cout << "That letter is not part of the word. Try again!" << std::endl;
                    incorrectGuesses.push_back(userGuess);
                    std::cout << "Here are all your incorrect guesses so far: ";
                    printIncorrectGuesses(incorrectGuesses);
                    numIncorrectGuesses++;
                }

                //Display num guesses right and wrong.
                totalGuesses = numIncorrectGuesses + numCorrectGuesses;
                std::cout << std::endl << "So far you have made " << totalGuesses << " total guess(es). " << std::endl;
                std::cout << numCorrectGuesses << " of them have been right";
                std::cout << " and " << numIncorrectGuesses << " of them have been wrong." << std::endl;

                //Loop until word is fully guessed. Keep track of how many guessed characters there are and compare to
                //the length of the secret word. If equal, end the game.
                unsigned int charChecker = 0;
                for (char i : unguessedWord) {
                    if (i == '-') {
                        wordFullyGuessed = false;
                        break;
                    }
                    else {
                        charChecker++;
                        continue;
                    }
                }
                if (charChecker == unguessedWord.size()) {
                    wordFullyGuessed = true;
                    std::cout << "You guessed the word!!" << std::endl;
                    std::cout << "It took you " << totalGuesses << " guesses to guess the word." << std::endl;
                    std::cout << std::endl;
                }
            }

        }


        //Ask if they want to play again
        std::cout << "Play again? (enter y/n)";
        char playAgain;
        std::cin  >> playAgain;
        if (playAgain == 'y' || playAgain == 'Y') {
            std::cout << std::endl;
            continue;
        }
        else {
            playGame = false;
            std::cout << "Tough... Thanks for playing! See ya next time.";
        }
    }
    return 0;
}

void printGreeting() {
    std::cout << "Welcome to hangman!" << std::endl;
}

std::string selectSecretWord() {
    srand(time(0));
    std::vector<std::string> wordBank;
    wordBank.emplace_back("quark");
    wordBank.emplace_back("zoology");
    wordBank.emplace_back("practices");
    wordBank.emplace_back("understanding");
    wordBank.emplace_back("onomatopoeia");
    wordBank.emplace_back("definition");
    wordBank.emplace_back("vector");
    wordBank.emplace_back("indexing");
    wordBank.emplace_back("icebreakers");
    wordBank.emplace_back("bump");
    int wordIndex = rand() % 10;
    return wordBank.at(wordIndex);
}

void printNumLettersInWord(std::string word, std::vector<char>& unguessedWord) {
    std::cout << "The secret word has " << word.size() << " letters." << std::endl;
    for (unsigned int i = 0; i < word.size(); ++i) {
        unguessedWord.at(i) = '-';
        std::cout << unguessedWord.at(i);
    }
    std::cout << std::endl;
}

char getUserGuess() {
    std::cout << "Please enter your letter guess: ";
    char userGuess;
    std::cin  >> userGuess;
    std::cout << std::endl;
    while (!isalpha(userGuess)) {
        if (!isalpha(userGuess)) {
            std::cout << "Sorry... expected an alpha character." << std::endl;
            std::cout << "Please enter an alpha character for your guess: ";
            std::cin  >> userGuess;
        }
        else {
            continue;
        }
    }
    return userGuess;
}

bool checkOldGuesses(char userGuess, std::vector<char> allGuesses) {
    bool alreadyGuessed = false;
    for (unsigned int i = 0; i < allGuesses.size(); ++i) {
        if (allGuesses.at(i) == userGuess) {
            alreadyGuessed = true;
            break;
        }
    }
    return alreadyGuessed;
}

void updateSecretWordVector(std::vector<char>& secretWord, std::vector<int>& correctGuessIndex,
                                         char userGuess) {
    for (int i : correctGuessIndex) {
        secretWord.at(i) = userGuess;
    }
    for (unsigned int i = correctGuessIndex.size() - 1; i >= 0; --i) {
        correctGuessIndex.erase(correctGuessIndex.begin() + i);
    }
}

void printIncorrectGuesses(std::vector<char> incorrectGuesses) {
    for (unsigned int i = 0; i < incorrectGuesses.size() - 1; ++i) {
        std::cout << incorrectGuesses.at(i) << ", ";
    }
    std::cout << incorrectGuesses.at(incorrectGuesses.size() - 1) << std:: endl;
}