void __cdecl Get_Controls(
	const int				*phase,		// Current phase number
	const int				*dimx,	    // Dimension of state vector X
	const int				*dimu,	    // Dimension of control vector U
	const int				*dimip,		// Dimension of integer parameter vector
	const int				*dimrp,	    // Dimension of real parameter vector
	const Phase_Info_Type	*fazinf,	// Record with additional phase info
	const double			*t,		    // Time t of evaluation
	const double			x[],	    // State vector X at time t
	const int				ipar[],	    // Integer parameter vector of phase
	const double			rpar[],     // Real parameter vector of phase
	double					*u,		    // Control vector U at time t
	double					*u_lb,		// Lower bounds for the control vector U
	double					*u_ub,		// Upper bounds for the control vector U
	int						*error)	    // Error flag
{
	/*	compute the control and its bounds as a function
	 *	of time, states and parameters. */

	double	*mee_coords_LCI;
	double	*cart_inert_coords_LCI;
	double	*v_vec_norm;
	double	*v_vec_norm_rotrad;
	double	**Q_transp;
	double	v_norm;
	int		i,j;

#ifdef DEBUG_MODE
printf("Get Controls\n");_flushall();
#endif

	*error = 0;

	mee_coords_LCI			= dvector(1,6);
	cart_inert_coords_LCI	= dvector(1,6);
	v_vec_norm				= dvector(1,3);
	v_vec_norm_rotrad		= dvector(1,3);
	Q_transp				= dmatrix(1,3,1,3);

	for (i=1; i<=3; i++){
		for (j=1; j<=3; j++){
			Q_transp[i][j]			= 0.0;
		}
		v_vec_norm[i]				= 0.0;
		v_vec_norm_rotrad[i]		= 0.0;
	}

	for (i=1; i<=6; i++) {
		mee_coords_LCI[i]			= x[i-1];
		cart_inert_coords_LCI[i]	= 0.0;
	}


	// Calculate velocity vector
	mee2cart(mee_coords_LCI, gmue[MOON], cart_inert_coords_LCI);

	v_norm = dvec_abs(&cart_inert_coords_LCI[3],3);
	for (i=1; i<=3; i++) {
		v_vec_norm[i] = cart_inert_coords_LCI[i+3] / v_norm;
	}

	ir_itheta_ih_transp(cart_inert_coords_LCI, Q_transp); //obtain Q_transp as [ir itheta ih]'
	dmat_times_vec(Q_transp, v_vec_norm, v_vec_norm_rotrad, 3, 3); //convert to rotating radial frame


	/* Initial control profile thrust tangentially to radius. */
	// Future work: set this initial guess separately for each phase
	u[0] =  -v_vec_norm_rotrad[1];//0.0;
	u[1] =  -v_vec_norm_rotrad[2];//-1.0;
	u[2] =  -v_vec_norm_rotrad[3];//0.0;
	
	u[3] =	1.0;//(cos(x[5])+1)/2;




	/* Bounds on control parameters */
	u_lb[0]	= LB_Control;
	u_ub[0]	= UB_Control;
	
	u_lb[1]	= LB_Control;
	u_ub[1]	= UB_Control;
		
	u_lb[2]	= LB_Control;
	u_ub[2]	= UB_Control;

	u_lb[3] = 0.0;
	u_ub[3] = 1.0;

	free_dvector(mee_coords_LCI,1,6);
	free_dvector(cart_inert_coords_LCI,1,6);
	free_dvector(v_vec_norm,1,3);
	free_dvector(v_vec_norm_rotrad,1,3);
	free_dmatrix(Q_transp,1,3,1,3);
}