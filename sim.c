#include "sim.h"

#define C_IMPL
extern void asm_do_row(Cell*, Cell*, size_t, size_t, size_t);

size_t mod(int x, size_t N) {
	return (x + x / N * N) % N;
}

static void do_row(Cell* dest, Cell* src, size_t row, size_t rows, size_t cols) {
	for(size_t col = 0; col < cols; col++){
		int alive = 0;
		for(int j = -1; j <= 1; j++){
			for(int k = -1; k <= 1; k++){
				if(j == 0 && k == 0){
					continue;
				}

				size_t rowneighbor = mod(row + j + rows, rows);
				size_t colneighbor = mod(col + k + cols, cols);

				size_t neighborindex = get_index(cols, rowneighbor, colneighbor);

				if(*(src + neighborindex) == 1){
					alive++;
				}
			}
		}
		if(*(src + get_index(cols, row, col)) == 1){
			if(alive == 2 || alive == 3){
				*(dest + get_index(cols, row, col)) = 1;
			}
			else{
				*(dest + get_index(cols, row, col)) = 0;
			}
		}
		else{
			if(alive == 3 || alive == 6){
				*(dest + get_index(cols, row, col)) = 1;
			}
			else{
				*(dest + get_index(cols, row, col)) = 0;
			}
		}
	}
}

void sim_loop(Board* board, unsigned int steps) {
	for(unsigned int i = 0; i < steps; i++){
		for(size_t j = 0; j < board->num_rows; j++){
			do_row(board->next_buffer, board->current_buffer, j, board->num_rows, board->num_cols);
		}
		swap_buffers(board);
		board->gen ++;
	}
}
