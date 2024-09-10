int strategy14( struct Sudoku* sud, unsigned int x, unsigned  int y ) {
	struct Combinator c;

	SudokuCell cellok;
	SudokuCell subset;
	SudokuCell changed;

	unsigned int i, j, k;
	unsigned int index[64] = { 0 };
	unsigned int combination[5] = { 0 };

	j = 0;

	//count number of empty cells in neighbourhood
	for( i = 0; i < sud->length; i++ ) {
		if( sud->cellvalue[x][i] == 0 && i != x ) {
			index[j++] = i;
		}
	}

	if( j <= SUDOKU_SUBSET_MIN ) return 0;

	//for defined subset sizes
	for( i = SUDOKU_SUBSET_MIN; i <= SUDOKU_SUBSET_MAX; i++ ) {
		Combinator_Initialize( &c, i, index, j );
		combination[i] = x;

		//for each available combination
		while( Combinator_GetNext( &c, combination ) == 0 ) {
			subset = 0ll;

			for( j = 0; j <= i; j++ ) {
				for( k = j + 1; k <= i; k++ ) {
					//combine all subsets
					//create validation mask
					if( sud->grid[y][combination[j]] & sud->grid[y][combination[k]] ) {
						cellok |= ( ( 1 << j ) | ( 1 << k ) );
						subset |= sud->grid[y][combination[j]] & sud->grid[y][combination[k]];
						break;
					}
				}
			}

			//validate subset
			if( __popcnt64( cellok ) != i + 1 ) continue;

			for( j = 0; j < sud->length; j++ ) {
				if( ( cellok & ( 1ll << j ) ) == 0 ) subset &= ( ~( sud->grid[y][j] ) );
			}

			if( __popcnt64( subset ) != i + 1 ) continue;

			//remove other candidates from cells in subset
			changed = 0;
			for( j = 0; j < sud->length; j++ ) {
				if( ( subset & ( 1ll << j ) ) != 0 ) {
					changed |= ( sud->grid[y][j] & ( ~( subset ) ) );
					sud->grid[y][j] &= subset;
				}
			}
			return changed != 0;
		}
	}


	return 0;
}