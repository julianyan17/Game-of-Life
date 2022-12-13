#include "cse30life.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - close the file
 * - return the boards pointer
 */
boards_t * createBoard(char *initFileName){
    FILE *fp;
    
    // allocate memory for the board 
    boards_t *board = malloc(sizeof(boards_t));

    // check if file to read is null
    if((fp = fopen(initFileName, "r")) == NULL) { 
            return NULL;
    }
    
    // read in the number of rows
    int rows;
    fscanf(fp,"%d", &rows);
    board->numRows = rows;

    // read in the number of columns
    int cols;
    fscanf(fp,"%d", &cols); 
    board->numCols = cols;

    // allocate memory for the both buffers
    board->bufferA = malloc(sizeof(belem) * rows * cols);
    board->bufferB = malloc(sizeof(belem) * rows * cols);

    board->currentBuffer = board->bufferA;
    board->nextBuffer = board->bufferB;

    // clear the board to initialize all the spaces
    clearBoards(board);

    // read in all the alive cells and set the element to 1 
    int rowCoor;
    int colCoor;
    while(fscanf(fp, "%d %d", &rowCoor, &colCoor) > 0) {
        int index = getIndex(board,rowCoor,colCoor);
        board->currentBuffer[index] = 1;
    }

    // close the file 
    fclose(fp);

    // set the starting generation to be 0
    board->gen = 0;
    return board;
}


/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){
    // get the address contained in bptrPtr
    boards_t *temp = *bptrPtr;

    // free everthing that was malloc-ed 
    free(temp->bufferA);
    free(temp->bufferB);
    free(temp);

    // set the memory address to null
    *bptrPtr = NULL;
}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
    int i;

    // store the length of the array
    int length = (self->numRows) * (self->numCols);

    // store the pointer at the buffers 
    belem *currBuffIdx = self->currentBuffer;
    belem *nextBuffIdx = self->nextBuffer;

    for(i = 0; i < length; i++) {
        // set the element at the pointer to the be and then increment
        *currBuffIdx = 0;
        currBuffIdx++;

        *nextBuffIdx = 0;
        nextBuffIdx++;
    }
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
    // create a temp to store currentBuffer
    belem *temp = self->currentBuffer;

    // swap next and current using temp
    self->currentBuffer = self->nextBuffer;
    self->nextBuffer = temp;
}


/**
 * get a cell index
 */
int getIndex(boards_t *self, int row, int col){
    int index = row * (self->numCols) + col;
    return index;
}
  
