int strategy5( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	unsigned int i, j;
	SudokuCell changed;

	//if cell contains more than 2 its not naked pair
	if( __popcnt64( sud->grid[y][x] ) != 2 ) return 0;

	for( i = 0; i < sud->length; i++ ) {
		if( i == y ) continue;

		//find identical partner
		if( sud->grid[i][x] == sud->grid[y][x] ) {
			changed = 0;
			for( j = 0; j < sud->length; j++ ) {
				//delete candidates from all other cells in neighbourhood
				if( j != i && j != y ) {
					changed |= ( sud->grid[j][x] & sud->grid[y][x] );
					sud->grid[j][x] &= ( ~( sud->grid[y][x] ) );
				}
			}

			return changed != 0;
		}
	}

	return 0;
}