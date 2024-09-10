EXPORT	void i_init_remap_and_rect_grid(
	RECT_GRID* r_grid)
{
	double		  *L = r_grid->L, *U = r_grid->U;
	int		  i, dim = r_grid->dim;
	const char	  **dnm, **Dnm, **dirs;
	static const char *plural[3] = { "", "s", "s"};

	prompt_for_remap(dim,&Remap);

	dnm = Remap.dnm;
	Dnm = Remap.Dnm;
	dirs = Remap.dirs;
	for (i = 0; i < dim; ++i)
	{
	    screen("Enter the computational limits in the "
	           "%s direction, %sL, %sU: ",dnm[i],Dnm[i],Dnm[i]);
	    (void) Scanf("%f %f\n",L+i,U+i);
	    if (U[i] <= L[i])
	    {
		screen("ERROR in i_init_remap_and_rect_grid(), "
		       "invalid computational limits L[%d] = %g, U[%d] = %g\n",
			i,L[i],i,U[i]);
		clean_up(ERROR);
	    }
	}

	screen("Enter the number%s of grid intervals of the\n\t",plural[dim-1]);
	screen("computational grid in the %s direction%s: ",dirs[dim-1],
	       plural[dim-1]);

	for (i = 0; i < dim; ++i)
	{
	    (void) Scanf("%d",&r_grid->gmax[i]);
	    r_grid->h[i] = (U[i] - L[i]) / r_grid->gmax[i];
	}
	(void) Scanf("\n"); /* Grab trailing newline */

	/* Set Default values for subdomain specifications */
	/* correct for scalar runs */
	set_rect_grid(L,U,L,U,NOBUF,NOBUF,r_grid->gmax,dim,&Remap,r_grid);
	Remap.area = r_grid->Remap.area;
}		/*end i_init_remap_and_rect_grid*/