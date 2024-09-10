void CustomPalette::slotRemoveColor()
{
    int i, j;
    if ( sel_row == -1 || sel_col == -1 )
    {
	//do nothing
    }
    else
    {
        if ( cur_col == 0 )
	{
	    cur_col = numCols() - 1;
	    cur_row--;
	}
	else
	    cur_col--;

        color_matrix[sel_row][sel_col] = invalid_color;
	color_names[sel_row][sel_col] = "";
	alpha_matrix[sel_row][sel_col] = -1;
	updateCell( sel_row, sel_col );

	QPtrList<Color> cl = k_toon -> document() -> getPalette() -> getColors();
	cl.setAutoDelete( true );
	cl.remove( map2Dto1D( sel_row, sel_col ) );
	cl.setAutoDelete( false );
	k_toon -> document() -> getPalette() -> setColors( cl );

	for ( i = sel_row; i < numRows(); i++ )
	{
	    if ( i == sel_row )
	    {
	        for ( j = sel_col; j < numCols(); j++ )
	        {
		    if ( j == numCols() - 1 && i < numRows() - 1 )
		    {
		        color_matrix[i][j] = color_matrix[i + 1][0];
		    	color_names[i][j] = color_names[i + 1][0];
			alpha_matrix[i][j] = alpha_matrix[i + 1][0];
		    	updateCell( i, j );
		    }
		    else if ( j < numCols() - 1 )
		    {
		    	color_matrix[i][j] = color_matrix[i][j + 1];
		    	color_names[i][j] = color_names[i][j + 1];
			alpha_matrix[i][j] = alpha_matrix[i][j + 1];
		    	updateCell( i, j );
		    }
		    else if ( j == numCols() - 1 && i < numRows() - 1 )
		    {
		    	color_matrix[i][j] = invalid_color;
		    	color_names[i][j] = "";
			alpha_matrix[i][j] = -1;
		    	updateCell( i, j );
		    }
	    	}
	    }
	    else
	    {
	        for ( j = 0; j < numCols(); j++ )
	        {
		    if ( j == numCols() - 1 && i < numRows() - 1 )
		    {
		        color_matrix[i][j] = color_matrix[i + 1][0];
		    	color_names[i][j] = color_names[i + 1][0];
			alpha_matrix[i][j] = alpha_matrix[i + 1][0];
		    	updateCell( i, j );
		    }
		    else if ( j < numCols() - 1 )
		    {
		    	color_matrix[i][j] = color_matrix[i][j + 1];
		    	color_names[i][j] = color_names[i][j + 1];
			alpha_matrix[i][j] = alpha_matrix[i][j + 1];
		    	updateCell( i, j );
		    }
		    else if ( j == numCols() - 1 && i < numRows() - 1 )
		    {
		    	color_matrix[i][j] = invalid_color;
		    	color_names[i][j] = "";
			alpha_matrix[i][j] = -1;
		    	updateCell( i, j );
		    }
	    	}
	    }
	}
	if ( cur_col == sel_col && cur_row == sel_row )
	{
	    sel_row = -1;
	    sel_col = -1;
	    updateCell( cur_row, cur_col );
	}
    }
}