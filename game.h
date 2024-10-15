/*                                                                                                                                                                           
Name: Lily Claire Gibson-Grossmann                                                                                                                                           
Course: CPSC 1070 Section 02                                                                                                                                                 
Date: April 9, 2024                                                                                                                                                          
Description: This is a version of the NYT Games game 'Strands'. The user will input a file with the size of the grid, length of word, and strand list.                       
The strand list is a list of letters. The game generates a board and the user will find words that the strand makes based on the length of the word they provided.           
The player can move anywhere left, right, up, down, or diagonal (i.e. maximum of 8 potential moves while in a cell).                                                         
The player can provide a dictionary, or use Clemson's dictionary to generate the correct words.                                                                              
*/

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strand.h"

#define DICT_PATH "/usr/share/dict/american-english"

FILE * open_data_file(int argc, char** argv);
FILE * open_dict_file(int argc, char** argv);
bool guessed_before(strand_t * strand, char* guess);
void print_instructions(strand_t * strand);
void play_game(strand_t * strand);
void close_data_file(FILE * file);;
void close_dict_file(FILE * file);
#endif
