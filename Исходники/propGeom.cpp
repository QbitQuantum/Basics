//==== Generate Fuse Component ====//
void PropGeom::generate()
{
	int i, j;

	//==== Copy Current Section Data into SectVec ====//
	sectVec[currSectID].chord     = chord();
	sectVec[currSectID].twist     = twist();
	sectVec[currSectID].x_off     = loc();
	sectVec[currSectID].y_off     = offset();

	Xsec_surf surf;
	surf.set_num_pnts( numPnts.iget() );
	surf.set_num_xsecs( sectVec.size()+2 );

	//==== Load Up Airfoil ====//
	for ( int ip = 0 ; ip < surf.get_num_pnts() ; ip++ )
		surf.set_pnt(0, ip, sectVec[0].foil->get_end_cap(ip) );	

	int numxs = sectVec.size();
	for ( i = 0 ; i < numxs ; i++ )
	{
		for ( j = 0 ; j < surf.get_num_pnts() ; j++ )
		{
			surf.set_pnt( i+1, j, sectVec[i].foil->get_pnt(j) );
		}
	}
	for ( int ip = 0 ; ip < surf.get_num_pnts() ; ip++ )
		surf.set_pnt(numxs+1, ip, sectVec[numxs-1].foil->get_end_cap(ip) );	

	//==== Build Up One Blade ====//
	double rad = diameter()/2.0;
	for ( i = 0 ; i < surf.get_num_xsecs() ; i++ )
	{
		int sid = i;

		if ( i > 0 ) sid = i-1;

		if ( i > (int)sectVec.size()-1 ) sid = (int)sectVec.size()-1;

		Section* sPtr = &(sectVec[sid]);
		surf.scale_xsec_x(  i, sPtr->chord()*rad );
		surf.scale_xsec_z(  i, sPtr->chord()*rad );
		surf.offset_xsec_x( i, -0.5*(sPtr->chord()*rad) );
		surf.rotate_xsec_y( i, 90.0 );
		surf.rotate_xsec_y( i, -sPtr->twist() - pitch() );
		surf.offset_xsec_y( i, sPtr->x_off()*rad );
		surf.offset_xsec_z( i, -sPtr->y_off()*rad );
	}

	//==== Set Flags So Trailing Edge Remains Sharp ====//
	surf.set_pnt_tan_flag( 0, Bezier_curve::SHARP );
	surf.set_pnt_tan_flag( 1, Bezier_curve::SHARP );
    int num_pnts  = surf.get_num_pnts();
	surf.set_pnt_tan_flag( num_pnts-1, Bezier_curve::SHARP );

	if ( !smoothFlag )
	{
		for ( i = 0 ; i < surf.get_num_xsecs() ; i++ )
		{
			surf.set_xsec_tan_flag( i, Bezier_curve::SHARP );
		}
	}
	else	// Sharpen End Caps
	{
		surf.set_xsec_tan_flag( surf.get_num_xsecs()-2, Bezier_curve::SHARP );
	}


	bezier_surf besurf;
	surf.load_bezier_surface( &besurf );
	int umax = besurf.get_u_max();
	int wmax = besurf.get_w_max();

	Xsec_surf smooth_surf;
	smooth_surf.set_num_pnts( (surf.get_num_pnts()-1)*numW + 1 );
	smooth_surf.set_num_xsecs( (surf.get_num_xsecs()-1)*numU + 1 );

	for ( i = 0 ; i < smooth_surf.get_num_xsecs() ; i++ )
	{
		double fu = (double)i/(double)(smooth_surf.get_num_xsecs()-1);
		double u  = fu*(double)umax;
		for ( j = 0 ; j < smooth_surf.get_num_pnts() ; j++ )
		{
			double fw = (double)j/(double)(smooth_surf.get_num_pnts()-1);
			double w  = fw*(double)wmax;
			vec3d p = besurf.comp_pnt( u, w );
			smooth_surf.set_pnt( i, j, p );
		}
	}

	//==== Load Blades into bladeVec ====//
	for ( int nb = 0 ; nb < (int)bladeVec.size() ; nb++ )
	{
		bladeVec[nb].set_num_pnts( smooth_surf.get_num_pnts() );
		bladeVec[nb].set_num_xsecs(  smooth_surf.get_num_xsecs() );

		//==== Load Points ====//
		for ( i = 0 ; i < smooth_surf.get_num_xsecs() ; i++ )
			for ( j = 0 ; j < smooth_surf.get_num_pnts() ; j++ )
				bladeVec[nb].set_pnt( i, j, smooth_surf.get_pnt( i, j ) );

		double xang = 360.0*(double)nb/(double)(bladeVec.size());

		for ( i = 0 ; i < bladeVec[nb].get_num_xsecs() ; i++ )
		{
			bladeVec[nb].rotate_xsec_z( i, cone_angle() );
			bladeVec[nb].rotate_xsec_x( i, xang );
		}
		bladeVec[nb].load_refl_pnts_xsecs();
		bladeVec[nb].load_hidden_surf();
		bladeVec[nb].load_normals();
		bladeVec[nb].load_uw();

	}

	for ( int i = 0 ; i < (int)sectVec.size() ; i++ )
		sectVec[i].SetGeomPtr( this );

	update_bbox();


}