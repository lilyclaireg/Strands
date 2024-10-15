/*                                                                                                                                                                           
Name: Lily Claire Gibson-Grossmann                                                                                                                                           
Course: CPSC 1070 Section 02                                                                                                                                                 
Date: April 9, 2024                                                                                                                                                          
Description: This is a version of the NYT Games game 'Strands'. The user will input a file with the size of the grid, length of word, and strand list.                       
The strand list is a list of letters. The game generates a board and the user will find words that the strand makes based on the length of the word they provided.           
The player can move anywhere left, right, up, down, or diagonal (i.e. maximum of 8 potential moves while in a cell).                                                         
The player can provide a dictionary, or use Clemson's dictionary to generate the correct words.                                                                              
*/

#include "strand.h"

// Returns pointer to populated strand struct
strand_t * create_strand(FILE * dataFP, FILE * dictFP) {
  // Allocate memory for strand and store strand data scanned from strand file
  strand_t * strand = (strand_t *)malloc(sizeof(strand_t));
  strand = scan_strand_file(dataFP, strand);
  // Allocates memory for dictionary and stores FULL dictionary from dict file
  Dictionary * full_dictionary = (Dictionary *)malloc(sizeof(Dictionary));
  full_dictionary = scan_dict_file(dictFP, full_dictionary, strand);
  // Creates a word list then frees the dictionary and returns strand
  create_word_list(strand, full_dictionary);
  free_dict(full_dictionary);  
  return strand;
}

// Returns true if the word is a correct word in the strand
bool is_word_in_strand(strand_t * strand, char * word) {
  for (int i = 0; i < strand->numWords; ++i) {
    if (strcmp(word, strand->words[i]) == 0) {
      return true;
    }
  }
  return false;
}

// Prints the strand matrix called from the main function
void print_strand_matrix(strand_t * strand) {
  for (int i = 0; i < strand->rows; ++i) {
    printf("\t+");
    for (int j = 0; j < strand->cols; ++j) {
      printf("---+");
    }
    printf("\n\t|");
    for (int j = 0; j < strand->cols; ++j) {
      printf(" %c |", strand->letters[i][j]);
    }
    printf("\n");
  }
  printf("\t+");
  for (int i = 0; i < strand->cols; ++i) {
    printf("---+");
  }
  printf("\n");
}

// Frees all the strands memory
void free_strand(strand_t * strand) {
  for (int i = 0; i < strand->rows; ++i) {
    free(strand->letters[i]);
  }
  free(strand->letters);
  for (int i = 0; i < strand->numWords; ++i) {
    free(strand->words[i]);
  }
  free(strand->words);
  for (int i = 0; i < strand->numCorrectGuesses; ++i) {
    free(strand->guessedWordsList[i]);
  }
  free(strand->guessedWordsList);
  free(strand);
}

// Scan in strand file saving ->rows, ->cols, and ->wordLen for the strand
strand_t * scan_strand_file(FILE * dataFP, strand_t * strand) {
  // Scan in rows, columns, and word length                                                                               
  fscanf(dataFP, "%d %d\n%d\n", &strand->rows, &strand->cols, &strand->wordLen);
  strand->letters = (char **)malloc((strand->rows + 1) * sizeof(char*));
  for (int i = 0; i < strand->rows; ++i) {
    strand->letters[i] = (char *)malloc((strand->cols + 1) * sizeof(char));
    for (int j = 0; j < strand->cols; ++j) {
      fscanf(dataFP, " %c", &strand->letters[i][j]);
    }
  }
  return strand;
}

// scan dict file and return file with full dictionary
Dictionary * scan_dict_file(FILE * dictFP, Dictionary * dictionary, strand_t * strand) {
  int numWords = 0;
  int totalWords = 0;
  int j = 0;
  char* readVals = (char *)malloc(26 * sizeof(char));
  // Counts number of words in full dict until end of file is reached
  while (fscanf(dictFP,"%s\n", readVals) != EOF) {
    totalWords += 1;
    if (strlen(readVals) == strand->wordLen) {
      numWords += 1;
    }
  }  
  free(readVals);
  rewind(dictFP);
  // Allocate memory for full dictionary
  dictionary->words = (char **)malloc((numWords + 1) * sizeof(char*));
  dictionary->size = numWords;
  
  // Scans each word into the dictionary
  for (int i = 0; i < totalWords; ++i) {
    fscanf(dictFP, "%s\n", readVals);
    if (strlen(readVals) == strand->wordLen) {
      dictionary->words[j] = (char *)malloc((strand->wordLen + 1) * sizeof(char));
      strcpy(dictionary->words[j], readVals);
      j += 1;
    }
  }
  // Returns dictionary with full list of words
  return dictionary;
}

// Frees the dictionary's memory
void free_dict(Dictionary * dictionary) {
  for (int i = 0; i < dictionary->size; ++i) {
    free(dictionary->words[i]);
  }
  free(dictionary->words);
}

// Creates the word list of possible answers in the strand
strand_t * create_word_list(strand_t * strand, Dictionary * dictionary) {
  int numLetters = strand->rows * strand->cols;
  char word[strand->wordLen];
  // Start by allocating too much memory to strand->words
  strand->words = (char **)malloc(200 * sizeof(char *));
  strand->numWords = 0;
  // Calls recursive function, starting recursion at each letter in the strand
  for (int i = 0; i < numLetters; ++i) {
    generateNumberOfWords(strand, 0, dictionary, word, i);
  }
  // Reallocate true memory
  strand->words = (char **)realloc(strand->words, strand->numWords * sizeof(char *));
  return NULL;
}

// Recursive function to generate the possible words in the strand
void generateNumberOfWords(strand_t * strand, int indexInWord, Dictionary * dictionary, char word[26], int index) {
  bool wordInList = false;
  // Base Case: Once the index is equal to the word length, checks the word
  if (indexInWord >= strand->wordLen) {
    word[indexInWord] = '\0';
    // Checks if the word is a valid word in the dictionary. If it is, checks that the user hasn't already guessed that word.
    for (int k = 0; k < dictionary->size; ++k) {
      if (strcmp(word, dictionary->words[k]) == 0) {
	for (int i = 0; i < strand->numWords; ++i) {
	  if (strcmp(word, strand->words[i]) == 0) {
	    wordInList = true;
	  }
	}
	if (wordInList == false) {
	  strand->words[strand->numWords] = (char *)malloc((strand->wordLen + 1) * sizeof(char));
	  strcpy(strand->words[strand->numWords], word);
	  strand->numWords += 1;
	  return;
	}
      }
    }
  }
   // int i represents direction of rows
  for (int i = -1; i <= 1; i++) {
    // int j represents direction of columns
    for (int j = -1; j <= 1; j++) {
      // calculates the cells above or below the current cell, along with cells to the left or right
      int newRow = index / strand->cols + i;
      int newCol = index % strand->cols + j;
      int newIndex = newRow * strand->cols + newCol;
      // Checks that newRow, newCol, and newIndex are all within bounds
      if ((newRow >= 0) && (newRow < strand->rows) && (newCol >= 0) && (newCol < strand->cols) && (newIndex >= 0) && (newIndex < strand->rows * strand->cols) && (newIndex != index) && (indexInWord < strand->wordLen)) {
	// Recursively builds all possible words
	word[indexInWord] = strand->letters[newRow][newCol];
	generateNumberOfWords(strand, indexInWord + 1,  dictionary, word, newIndex);
   
      }
    }
  }
}


