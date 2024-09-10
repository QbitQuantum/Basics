/*
	Gets the window for coordinate [r,c]
*/
void getWindow( const Image& im, int window[][24], int r, int c ){
	
	// Gather window data
	for ( int i = r; i < r+24; i++ )
		for ( int j = c; j < c+24; j++ )
			window[i][j] = im.getPixel( i,j );
}