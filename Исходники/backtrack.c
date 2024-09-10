int main(void)
{
	struct point p;
	int ways = 0;

	printf( "hello, maze! \n" );
	print_maze();

	/* init start situation */ 
	p = start;
	maze[p.row][p.col] = 2;
	push(p);
	print_maze();

	while( !is_empty() )
	{
		print_stack();
		/* get the saved point from stack */
		p = pop();

		/* judge if p is target point */
		if( p.row == target.row && p.col == target.col )
		{
			printf( "target is found! \n" );
			print_stack();

			/* print backward road */
			printf( "%d solution as follows: \n", ++ways );
			print_solution();
			getchar();

			// assume p is the target point
			backtrack( p );
			continue;
		}

		int flag = 0;
		/* expend p to UP, LEFT, DOWN, RIGHT */
		// look UP
		if( p.row-1 >= 0 && maze[p.row-1][p.col] == 0 )
			flag = visit( p.row-1, p.col, p );	

		// look LEFT 
		if( p.col-1 >= 0 && maze[p.row][p.col-1] == 0 )
			flag = visit( p.row, p.col-1, p );

		// look DOWN 
		if( p.row+1 < MAX_ROW && maze[p.row+1][p.col] == 0 )
			flag = visit( p.row+1, p.col, p );

		// look RIGHT 
		if( p.col+1 < MAX_COL && maze[p.row][p.col+1] == 0 )
			flag = visit( p.row, p.col+1, p );

		// backtrack clear 0
		if( flag == 0 )
			backtrack( p );

		print_maze();
		print_pre();
		print_stack();
		getchar();
	}

	printf( "there is %d ways out! \n", ways );

	return 0;
}