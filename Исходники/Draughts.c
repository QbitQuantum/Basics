int main()
{
	char board[BOARD_SIZE][BOARD_SIZE];
	init_board(board);
	board[3][3] = WHITE_K;
	//board[2][4] = BLACK_M;
	//board[4][4] = BLACK_M;
	//board[5][7] = EMPTY;
	print_board(board);
	print_message(WRONG_MINIMAX_DEPTH);
	perror_message("TEST");
	Move* m = get_all_moves(board, WHITE);
	print_moves(m);
	scanf_s("DONE");
	return 0;
}