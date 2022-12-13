Author: Julian Yan  
Date: 11/06/2019  
Title: Game of Life  
Summary: This program implements Conway's Game of Life.

Contents: 
* board.c
  * This file creates the board from a file to simulate the Game of Life. 
    * boards_t * createBoard(char *initFileName)
    * void deleteBoard(boards_t **bptrPtr)
    * void clearBoards(boards_t *self)
    * void swapBuffers(boards_t *self)
    * int getIndex(boards_t *self, int row, int col)
* board.h
  * This file contains the header file for board.c.
* cse30life.h
  * This file contains functions to support the similuation of the Game of Life. 
* main.c
  * This file parses the files and displays the created similuation of the Game of Life. 
    * void printHelp(const char *name)
    * void parseOpts(int argc, char **argv, options_t *userOptsP)
    * int main(int argc, char **argv)
* sim.c
  * This file performs the simulations based on the conditions of the Game of Life. 
    * void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols)
    * void simLoop(boards_t *self, uint32_t steps)
* sim.h 
  * This file contains the header file for sim.h.
* test
  * config.big
  * config.fancy
  * config.small 
  * life 
  * life_sol