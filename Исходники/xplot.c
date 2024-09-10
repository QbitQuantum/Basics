void xp_fill_polygon(int num_points,
			float* x_vals, float* y_vals)
{
	int *xp,*yp;
	int i;
	float fx,fy;

	if( plot_vp == NO_VIEWER ) return;

	/* BUG should scale the points */
	xp = (int *) getbuf( num_points * sizeof(int) );
	yp = (int *) getbuf( num_points * sizeof(int) );

	for(i=0;i<num_points;i++){
		fx=x_vals[i]; fy=y_vals[i];
		scale_fxy(plot_vp,&fx,&fy);
		xp[i] = (int) nearbyintf(fx);
		yp[i] = (int) nearbyintf(fy);
	}

	_xp_fill_polygon(plot_vp, num_points, xp, yp);

	givbuf(xp);
	givbuf(yp);
}