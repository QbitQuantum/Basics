//Naked pairs box
int rule6( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	unsigned int i, j;
	SudokuCell changed;

	if( __popcnt64( sud->grid[y][x] ) != 2 ) return 0;

	for( i = 0; i < sud->length; i++ ) {
		if( ( ( sud->grid[y][x] ) == ( *sud->cellbox[y][x][i] ) ) && ( &sud->grid[y][x] ) != sud->cellbox[y][x][i] ) {
			changed = 0;
			for( j = 0; j < sud->length; j++ ) {
				if( (j != i) && (sud->cellbox[y][x][j] != &sud->grid[y][x])) {
					changed |= ( ( *sud->cellbox[y][x][j] ) & sud->grid[y][x] );
					*sud->cellbox[y][x][j] &= ( ~( sud->grid[y][x] ) );
				}
			}
			return changed != 0;
		}
	}

	return 0;
}