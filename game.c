/*
Name: Lily Claire Gibson-Grossmann
Course: CPSC 1070 Section 02
Date: April 9, 2024
Description: This is a version of the NYT Games game 'Strands'. The user will input a file with the size of the grid, length of word, and strand list.
The strand list is a list of letters. The game generates a board and the user will find words that the strand makes based on the length of the word they provided.
The player can move anywhere left, right, up, down, or diagonal (i.e. maximum of 8 potential moves while in a cell).
The player can provide a dictionary, or use Clemson's dictionary to generate the correct words.
*/


#include "game.h"

// If arguments are less than one, prompts for filename. Else, opens provided file.
// Returns pointer to strand file
FILE * open_data_file(int argc, char** argv) {
  char * fileName = (char *)malloc(100 * sizeof(char));
  if (argc >= 1 && argv[1] != NULL) {
    strcpy(fileName, argv[1]);
  }
  else {
    printf("Provide strand data filename:\n");
    scanf(" %s", fileName);
  }
  if (fileName == NULL) {
    printf("NULL");
    return NULL;
  }
  FILE * file = fopen(fileName, "r");
  free(fileName);
  return file;
}

// If arguments are less than two, opens default dict. Else, opens provided dict.
// Returns pointer to dict file
FILE * open_dict_file(int argc, char** argv) {
  char fileName[100];
  if (argc >= 2 && argv[2] != NULL) {
    strcpy(fileName, argv[2]);
  }
  else {
    strcpy(fileName, DICT_PATH);
  }
  FILE * file = fopen(fileName, "r");
  return file;
}

// Prints instructions
void print_instructions(strand_t * strand) {
  printf("\n  +-- Welcome to Strands! --+\n");
  printf("\nInstructions:\n");
  printf("\tFind all %d %d-letter words\n", strand->numWords, strand->wordLen);
  printf("\tEach word's letters must touch\n");
  printf("\tA letter can be repeated in a word\n");
  printf("\tType a word then press 'Enter'\n");
  printf("\tType 'quit' when done\n");
}


// Funciton to play the game
void play_game(strand_t * strand) {
  char userInput[27];
  bool correctGuess;

  printf("\nGuess a word or 'quit':\n");
  scanf(" %s", userInput);
  strand->guessedWordsList = (char **)malloc(strand->numWords * sizeof(char *));
  strand->numCorrectGuesses = 0;

  while ((strcmp(userInput, "quit") != 0) && (strand->numCorrectGuesses < strand->numWords)) {
    // Sends to bool function in strand.c
    // checks if guess is correct
    correctGuess = is_word_in_strand(strand, userInput);

    if (correctGuess == true) {
      // if guess is correct, validates word hasnt been previously guessed
      if (guessed_before(strand, userInput) == true) {
        printf("You have already guessed %s!\n", userInput);
      }
      else {
	printf("%s is a valid word in the strand!\n", userInput);
	strand->guessedWordsList[strand->numCorrectGuesses] = (char *)malloc(26 * sizeof(char));
	strcpy(strand->guessedWordsList[strand->numCorrectGuesses], userInput);
	strand->numCorrectGuesses += 1;
      }
    }
    else {
      printf("%s is not a valid word in the strand.\n", userInput);
    }

    // Prints remaining words and prompts user for input
    if (strand->numCorrectGuesses != strand->numWords) {
      printf("You have found %d of %d %d-letter words in the strand so far.\n", strand->numCorrectGuesses, strand->numWords, strand->wordLen);
    }
    if (strand->numCorrectGuesses < strand->numWords) {
      printf("\nGuess a word or 'quit':\n");
      scanf(" %s", userInput);
    }
  }

  //Prints appropriate output statement
  if (strand->numCorrectGuesses >= strand->numWords) {
    printf("You found all %d %d-letter words!\n", strand->numWords, strand->wordLen);
    printf("Great job! Thanks for playing!\n");
  }
  else {
    printf("You found %d out of %d %d-letter words.\n", strand->numCorrectGuesses, strand->numWords, strand->wordLen);
    printf("Thanks for playing!\n");
  }
}

void close_data_file(FILE * file) {
  fclose(file);
}

void close_dict_file(FILE * file) {
  fclose(file);
}

bool guessed_before(strand_t * strand, char* guess) {
  for (int i = 0; i < strand->numCorrectGuesses; ++i) {
    if (strcmp(strand->guessedWordsList[i], guess) == 0) {
      return true;
    }
  }
  return false;
}

