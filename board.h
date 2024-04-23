#ifndef _BOARD_H
#define _BOARD_H
#include "life.h"

typedef unsigned char Cell;

typedef struct {
	Cell* buffer_a; 
	Cell* buffer_b; 
	size_t num_rows; 
	size_t num_cols;
	Cell* current_buffer;
	Cell* next_buffer;
	unsigned int gen;
} Board;

extern Board* create_board(const char* filename);
extern void delete_board(Board** board);
extern void clear_board(Board* board);
extern void swap_buffers(Board* board);
extern void sim_step(Board* board, unsigned int steps);
extern void set_sim(Board* board, void (*sim)(Board* board, unsigned int steps));
extern size_t get_index(size_t num_cols, size_t row, size_t col);

#endif
