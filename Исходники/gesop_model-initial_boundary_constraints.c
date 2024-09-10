void __cdecl Initial_Boundary_Constraints(
	const int				*phase,		// Current phase number
	const int				*dimx,		// Dimension of state vector X
    const int				*dimu,		// Dimension of control vector U
	const int				*dimip,		// Dimension of integer parameter vector
	const int				*dimrp,		// Dimension of real parameter vector
	const Phase_Info_Type	*fazinf,	// Record with additional phase info
	const double			*t,			// Time t of evaluation
	const double			x[],		// State vector X at time t
	const double			u[],		// Control vector U at time t
	const int				ipar[],		// Integer parameter vector of phase
	const double			rpar[],		// Real parameter vector of phase
	const int				*dimbc,		// dimension of boundary constraint vector
	const Decision_Type		evalc[],	// Which constraints to evaluate
	double          		*bcon,		// Vector of boundary constraints
 	int             		*error		// Error flag
	)
{
	/* computes the boundary constraints associated with the initial
	 * time of the optimal control problem (t0 of *phase)
	 * as a function of the initial time, the state- and control
	 * vector at time t0 and the real parameter vector of *phase. */
	
	double	*mee_coords_LCI;			// contains the first six elements of the state, ie the equ. elements
	double	*kep_coords_LCI;			// contains the first six elements of the state in earth centred keplerian elements
	int		i;

#ifdef DEBUG_MODE
printf("Initial Boundary Constraints\n");_flushall();
#endif
	
	*error = 0;

		// Initialise storage
		mee_coords_LCI			= dvector(1,6);				
		kep_coords_LCI			= dvector(1,6);				
				
		for (i=1; i<=6; i++) {
			mee_coords_LCI[i]			= x[i-1];
			kep_coords_LCI[i]			= 0.0;
		}

		// Calculate parameters
		mee2kep(mee_coords_LCI, kep_coords_LCI);

		/* Semimajor axis = 1,838km */
		if (evalc[0] == yes) {
			bcon[0] = 1.0 - kep_coords_LCI[1]/1.838e6;
		}

		/* Eccentricity < 0.1 */
		if (evalc[1] == yes) {
			bcon[1] = 0.1 - kep_coords_LCI[2];
		}

		/* Inclination = 70° */
		if (evalc[2] == yes) {
			bcon[2] = kep_coords_LCI[3]*R2D/70 - 1.0;
		}

		/* Time = 1000 days */
		if (evalc[3] == yes) {
			bcon[3] =  x[6]/1000 - 1.0;
		}

		/* Mass = 100.0kg */
		if (evalc[4] == yes) {
			bcon[4] =  x[7]/100.0 - 1.0;
		}


		// Free memory
		free_dvector(mee_coords_LCI,1,6);
		free_dvector(kep_coords_LCI,1,6);

}