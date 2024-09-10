//naked subset column
int rule9( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	unsigned int i, changed, subset, ctPartners;
	unsigned int partners[5];

	for( subset = 5; subset >= 3; subset-- ) {
		if( __popcnt64( sud->grid[y][x] ) > subset ) continue;
		if( __popcnt64( sud->contains[CONTAINS_COL][y] ) < subset ) continue;

		ctPartners = 0;
		for( i = 0; i < sud->length; i++ ) {
			if( ( i != y ) && ( sud->grid[i][x] & sud->grid[y][x] ) && ( ( sud->grid[i][x] & ( ~sud->grid[y][x] ) ) == 0 ) ) {
				partners[ctPartners++] = i;
			}
		}

		if( ctPartners != subset ) continue;

		changed = 0;
		for( i = 0; i < sud->length; i++ ) {
			changed |= ( sud->grid[i][x] & ( ~sud->grid[y][x] ) );
			sud->grid[i][x] &= ( ~sud->grid[y][x] );
		}

		return changed;
	}

	return 0;
}