/*                                                                                                                                                                           
Name: Lily Claire Gibson-Grossmann                                                                                                                                           
Course: CPSC 1070 Section 02                                                                                                                                                 
Date: April 9, 2024                                                                                                                                                          
Description: This is a version of the NYT Games game 'Strands'. The user will input a file with the size of the grid, length of word, and strand list.                       
The strand list is a list of letters. The game generates a board and the user will find words that the strand makes based on the length of the word they provided.           
The player can move anywhere left, right, up, down, or diagonal (i.e. maximum of 8 potential moves while in a cell).                                                         
The player can provide a dictionary, or use Clemson's dictionary to generate the correct words.                                                                              
*/

#ifndef STRAND_H
#define STRAND_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct strand {
  char** words;
  char** letters;
  char** guessedWordsList;
  int rows, cols;
  int numWords;
  int wordLen;
  int numCorrectGuesses;
} strand_t;

typedef struct dict_struct {
  char** words;
  int size;
} Dictionary;

strand_t * create_strand(FILE * dataFP, FILE * dictFP);
strand_t * scan_strand_file(FILE * dataFP, strand_t * strand);
strand_t * create_word_list(strand_t * strand, Dictionary * dictionary);
Dictionary * scan_dict_file(FILE * dictFP, Dictionary * dictionary, strand_t * strand);
bool is_word_in_strand(strand_t * strand, char * word);
void print_strand_matrix(strand_t * strand);
void free_strand(strand_t * strand);
void free_dict(Dictionary * dictionary);
void generateNumberOfWords(strand_t * strand, int indexInWord, Dictionary * dictionary, char word[26], int index);

#endif
