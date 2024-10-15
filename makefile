                                                                                                                                                                           
#Name: Lily Claire Gibson-Grossmann                                                                                                                                           
#Course: CPSC 1070 Section 02                                                                                                                                                 
#Date: April 9, 2024                                                                                                                                                          
#Description: This is a version of the NYT Games game 'Strands'. The user will input a file with the size of the grid, length of word, and strand list.                       
#The strand list is a list of letters. The game generates a board and the user will find words that the strand makes based on the length of the word they provided.           
#The player can move anywhere left, right, up, down, or diagonal (i.e. maximum of 8 potential moves while in a cell).                                                         
#The player can provide a dictionary, or use Clemson's dictionary to generate the correct words.                                                                             

CC = gcc
CFLAGS = -Wall

EXECUTABLE = strands.exe
MAIN = main.c

# Includes the file containing SOURCES and HEADERS
include defs.mk

$(EXECUTABLE): $(MAIN) $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(MAIN) $(SOURCES)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
