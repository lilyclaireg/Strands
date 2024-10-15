/*                                                                                                                                                                           
Name: Lily Claire Gibson-Grossmann                                                                                                                                           
Course: CPSC 1070 Section 02                                                                                                                                                 
Date: April 9, 2024                                                                                                                                                          
Description: This is a version of the NYT Games game 'Strands'. The user will input a file with the size of the grid, length of word, and strand list.                       
The strand list is a list of letters. The game generates a board and the user will find words that the strand makes based on the length of the word they provided.           
The player can move anywhere left, right, up, down, or diagonal (i.e. maximum of 8 potential moves while in a cell).                                                         
The player can provide a dictionary, or use Clemson's dictionary to generate the correct words.

NOTE: This is a project for CPSC1070 at Clemson University, taught by Professor Alex Adkins. This project will no longer be used for this course, hence it is okay to publish this code.                                                                              
*/

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "strand.h"

int main(int argc, char** argv) {
  // Open strand data file in 'game.c'
  // Sends in int argc and int** argv
  // Returns file pointer to strands info file
  FILE * dataFP = open_data_file(argc, argv);
  if (dataFP == NULL) return 0;
  
  
  // Open dictionary file in 'game.c'
  // Sends in int argc and int** argv
  // Returns file pointer to dictionary file
  FILE * dictFP = open_dict_file(argc, argv);
  if (dataFP == NULL) return 0;

  // Create strand struct in 'strand.c'
  // Sends in strand file and dictionary file
  // Returns pointer to populated strand struct
  strand_t * strand = create_strand(dataFP, dictFP);
  if (strand == NULL) return 0;

  // Print strand and game instructions
  // Print strand from 'strand.c'
  // Print instructions from 'game.c'
  print_strand_matrix(strand);
  print_instructions(strand);

  // Play the game from 'game.c'
  play_game(strand);

  // Free all strand memory
  free_strand(strand);
  // Free strand data file
  close_data_file(dataFP);
  // Free dict file
  close_dict_file(dictFP);
  
  return 0;
}
