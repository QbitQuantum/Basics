void perspective(TrformStr *TrPtr, pPrefs *prefs) 	
{
	double 		v[3];										// auxilliary vector
	double 		points_per_degree;							
	double 		mt[3][3];
	double  	alpha, beta, gammar; 				// Angles in rad
	double		x_off, y_off, d;
	double		a;
	uint32_t   	destwidth, destheight;
	fDesc		fD;

	void		*params[4];		// Parameters for perspective control functions
	
	params[0] = (void*)mt;
	params[1] = (void*)&d;
	params[2] = (void*)&x_off;
	params[3] = (void*)&y_off;	



	// Set destination image parameters


	destwidth 		= prefs->width;
	destheight 		= prefs->height;

	if( destwidth <= 0 || destheight <= 0 )
	{
		TrPtr->success = 0;
		PrintError( "Zero Destination Image Size" );
		return;
	}


	if( SetDestImage(TrPtr, destwidth, destheight) != 0 ) 
	{
		TrPtr->success = 0;
		PrintError( "Not enough Memory.");
		return;
	}
	
	
	// Set parameters for perspective transformation
	
	
	a = DEG_TO_RAD( prefs->hfov );
	
	alpha 	=  DEG_TO_RAD( prefs->y_beta );
	beta  	=  DEG_TO_RAD( prefs->x_alpha );
	gammar 	=  DEG_TO_RAD( prefs->gamma   );
	
	fD.func =(trfn)NULL; 

	switch(prefs->format)
	{
		case _rectilinear:
			if( a >= PI )
			{
				TrPtr->success = 0;
				PrintError("HFOV must be smaller than 180 degrees");
				return;
			}
			d = TrPtr->src->width / ( 2.0 * tan( a/2.0 ) );
			if( prefs->unit_is_cart )
			{
				alpha =  atan( (prefs->y_beta - TrPtr->src->height/2.0 ) / d );
				beta  = - atan( (prefs->x_alpha - TrPtr->src->width/2.0 ) / d );
			}
			fD.func = persp_rect;
			break;
		case _spherical_tp:
			d = TrPtr->src->width / a;
			if( prefs->unit_is_cart )
			{
				points_per_degree 		= ((double) TrPtr->src->width) / (a * 360 / (2 * PI)) ;
				alpha	= ((TrPtr->src->height/2.0 - prefs->y_beta)/ points_per_degree) * 2 * PI / 360;
				beta	= -((TrPtr->src->width/2.0  - prefs->x_alpha)/ points_per_degree) * 2 * PI / 360;

			}
			fD.func = persp_sphere;
			break;
	}

	SetMatrix( alpha, beta, gammar , mt, 1 );

		// Offset
	
	v[0] = 0.0; 
	v[1] = 0.0;
	v[2] = d;
	matrix_mult( mt, v );
	x_off =  v[0]*d/v[2];
	y_off =  v[1]*d/v[2];


	// Do transformation


	if( fD.func != NULL)
	{
		fD.param = params;
		//transFormEx( TrPtr, &fD, &fD, 0, 1 );
        transForm( TrPtr, &fD, 0 );
	}
	else
		TrPtr->success = 0;

	if( TrPtr->success == 0 && ! (TrPtr->mode & _destSupplied))	// Moved here
			myfree( (void**)TrPtr->dest->data );

}