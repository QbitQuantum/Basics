void Maze::generateKruskal( unsigned long seed, bool frame, bool verbose )
{
	unsigned long i, j, x, y, wallcount;
	std::clock_t timer = std::clock( );
	std::vector <Point> walls;
	Point f[2]; //Fields to compare

	//Quit if not ready
	if ( !this->ready ) return;

	//Random seed
	srand( seed );

	//Fill with 1's
	for ( i = 0; i < this->width; i++ )
		for ( j = 0; j < this->height; j++ )
			this->data[i][j] = 1;

	//Add grid made of walls
	for ( i = 0; i < this->width; i++ )
		for ( j = 0; j < this->height; j++ )
		{
			this->data[i][j] = ( j % 2 ) ? 0 : !( i % 2 ) * ( j * this->width + i + 1 );

			if ( i == this->width - 1 && !( this->width % 2 ) )
				this->data[i][j] = !( j % 2 );

			if ( j == this->height - 1 && !( this->height % 2 ))
				this->data[i][j] = !( i % 2 );
		}

	//List all walls
	for ( i = 0; i < this->width; i++ )
		for ( j = 0; j < this->height; j++ )
			if ( this->data[i][j] == 0 ) walls.push_back( Point( i, j ) );

	wallcount = walls.size( );

	//While there are walls
	while ( walls.size( ) )
	{
		//Random wall
		i = rand( ) % walls.size( );
		x = walls[i].x;
		y = walls[i].y;

		f[0] = f[1] = walls[i];
		f[0].x--;
		f[1].x++;

		if ( get( f[0] ) != get( f[1] ) && get( f[0] ) != 0 && get( f[1] ) != 0 )
		{
			this->data[x][y] = get( f[0] );
			floodfill( x, y, get( f[0] ), get( f[1] ) );
		}
		else
		{
			f[0] = f[1] = walls[i];
			f[0].y--;
			f[1].y++;

			if ( get( f[0] ) != get( f[1] ) && get( f[0] ) != 0 && get( f[1] ) != 0 )
			{
				this->data[x][y] = get( f[0] );
				floodfill( x, y, get( f[0] ), get( f[1] ) );
			}
		}

		walls[i] = walls[walls.size( ) - 1];
		walls.erase( walls.begin( ) + walls.size( ) - 1 ); //Remove wall from walls index
		

		//Output progress message
		if ( verbose ) std::cerr << std::fixed << std::setprecision( 2 ) <<  "\rProgress: " << 100.0 - ( (double)walls.size( ) / (double)wallcount * 100.0 ) << "%";
	}

	//Final cleanup to 1's and 0's
	for ( i = 0; i < this->width; i++ )
		for ( j = 0; j < this->height; j++ )
			this->data[i][j] = this->data[i][j] != 0;

	//Draw frame
	if ( frame )
	{
		for ( i = 0; i < this->width; this->data[i++][0] = 0 ); //Top
		for ( i = 0; i < this->width; this->data[i++][this->height - 1] = 0 ); //Bottom
		for ( i = 0; i < this->height; this->data[0][i++] = 0 ); //Left
		for ( i = 0; i < this->height; this->data[this->width - 1][i++] = 0 ); //Right
	}

	//Output time elapsed
	if ( verbose ) std::cerr << std::fixed << std::setprecision( 2 ) << "\nTime elapsed: " << (double)( std::clock( ) - timer ) / (double)CLOCKS_PER_SEC << "s" << std::endl;
}