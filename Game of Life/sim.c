/**
 * Assignment: SWLife
 * Section: (A, B, C)
 * Class: UCSD CSE30-fall2019
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, belem *, uint32_t);

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols){
    // initalize number of aliveCells to be 0
    int aliveCells = 0;

    // store the pointer of srcStart
    belem *temp = srcStart;
    for(int i = 0; i < cols - 2; i++) {
        // store the value at the pointer 
        belem value = *temp; 

        // check for dead or alive neighbors
        if((*(temp + 1)) == 1) {
            aliveCells++;
        }
        if((*(temp - 1)) == 1) { 
            aliveCells++;
        }
        if((*(temp + cols)) == 1) {
            aliveCells++;
        }
        if((*(temp - cols)) == 1) {
            aliveCells++;
        }
        if((*(temp + cols - 1)) == 1) {
            aliveCells++;
        }
        if((*(temp - cols - 1)) == 1) {
            aliveCells++;
        }
        if((*(temp - cols + 1)) == 1) {
            aliveCells++;
        }
        if((*(temp + cols + 1)) == 1) {
            aliveCells++;
        }
    
        // check whether or not cell will be alive next generation
        if(value == 1 && (aliveCells == 0 || aliveCells == 1)) {
            *dest = 0;
            dest++;
        }

        else if(value == 1 && (aliveCells == 2 || aliveCells == 3)) {
            *dest = 1;
            dest++;
        }
        
        else if(value == 1 && aliveCells >=4) {
            *dest = 0;
            dest++;
        }

        else if(value == 0 && aliveCells == 3) {
            *dest = 1;
            dest++;
        }

        else if(value == 0 && aliveCells != 3) {
            *dest = 0;
            dest++;
        }

        // increment the pointer, set aliveCells back to 0
        temp++;
        aliveCells = 0;
    }
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, uint32_t steps){
    for(int i = 0; i < steps; i++) {
        // store the length of a row
        int length = self->numCols - 2;

        // store the address of the first possible alive cell in nextBuffer
        belem *temp = self->nextBuffer + self->numCols + 1;

        // store the address the start and the end of a row in currentBuffer
        belem *start = self->currentBuffer + self->numCols + 1;
        belem *end = start + length - 1;

        // call doRow the number of times of possible alive rows
        for(int j = 1; j < (self->numRows) - 1; j++) {
            doRow(temp, start, end, self->numCols); 
            // increment all pointers to the next row
            temp = temp + self->numCols;
            start = start + self->numCols;
            end = end + self->numCols;
        }
        swapBuffers(self);

        // increment the generation
        (self->gen)++;
    }
}




