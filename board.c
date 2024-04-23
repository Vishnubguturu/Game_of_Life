#include "life.h"
#include "board.h"

Board* create_board(const char* filename) {
	//malloced a board structure
	Board* board = (Board*) malloc(sizeof(Board));
	if(board == NULL){
		free(board);
		return NULL;
	}

	//set gen to 0
	board->gen = 0;

	//opened the file and checked for NULL
	FILE* file = fopen(filename, "r");
	if(file == NULL){
		free(board);
		return NULL;
	}

	size_t num1 = 0;
	size_t num2 = 0;
	//reading first and second line for rows and cols
	if(fscanf(file, "%zu", &num1) == 1){
		board->num_rows = num1;
	}
	if(fscanf(file, "%zu", &num2) == 1){
		board->num_cols = num2;
	}
	else{
		free(board);
		fclose(file);
		return NULL;
	}

	//malloced buffer_a and buffer_b and checked for null
	board->buffer_a = (Cell*) malloc(sizeof(Cell)*board->num_rows*board->num_cols);
	board->buffer_b = (Cell*) malloc(sizeof(Cell)*board->num_rows*board->num_cols);
	if(board->buffer_a == NULL || board->buffer_b == NULL){
		free(board->buffer_a);
		free(board->buffer_b);
		free(board);
		fclose(file);
		return NULL;
	}

	//aliased current_buffer to buffer_a and next_buffer to buffer_b
	board->current_buffer = board->buffer_a;
	board->next_buffer = board->buffer_b;
	clear_board(board);

	//setting cells in current_buffer
	size_t num3 = 0;
	size_t num4 = 0;
	while(fscanf(file, "%zu %zu", &num3, &num4) == 2){
		*(board->current_buffer + get_index(board->num_cols, num3, num4)) = 1;
		
	}

	//closing the file
	fclose(file);
	return board;
}

/**
 * delete a board
 */
void delete_board(Board** bpp) {
	free((*bpp)->buffer_a);
	free((*bpp)->buffer_b);
	free(*bpp);
	*bpp = NULL;
}

/**
 * set all the Cells in both buffers to 0
 */
void clear_board(Board* board) {
	for(size_t i = 0; i < board->num_rows*board->num_cols; i++){
		board->buffer_a[i] = 0;
		board->buffer_b[i] = 0;
	}
}

/**
 * swap the current and next buffers
 */
void swap_buffers(Board* board) {
	Cell* temp = board->current_buffer;
	board->current_buffer = board->next_buffer;
	board->next_buffer = temp;
}

/**
 * get a cell index
 */
size_t get_index(size_t num_cols, size_t row, size_t col) {
	return row * num_cols + col;
}
