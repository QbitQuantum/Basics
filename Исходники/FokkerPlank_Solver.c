void _solveFP(const double * abgth,
				const double * phis, const int N_phi,
				const double * ts, const int num_steps, //num_steps is not the best way to call this variable it is actually num_epochs or num_tks
				const double * xs, const int num_nodes,
				double *** Fs) {

//	printf("a,b,g,t = %.2f %.2f %.2f %.2f", abgth[0],abgth[1],abgth[2],abgth[3]);
//	double *** Fs;
//	= new double[N_phi][num_steps][num_nodes];
//	double * contiguousAllocationPtr = malloc(N_phi*num_steps*num_nodes * sizeof(double));
//	Fs = malloc(N_phi * sizeof(double**));

//	for (int phi_idx = 0; phi_idx < N_phi; ++phi_idx) {
//		for (int t_idx = 0; t_idx < num_steps; ++t_idx) {
//			for (int x_idx = 0; x_idx < num_nodes; ++x_idx) {
//				Fs[phi_idx][t_idx][x_idx] = phis[phi_idx]*ts[t_idx]*xs[x_idx];
//			}
//		}
//	}
	//RIP PARAMS:
	double alpha, beta, gamma, theta;
	double dx, dt;
	alpha = abgth[0]; beta= abgth[1]; gamma =abgth[2]; theta = abgth[3];
	dt = ts[1]-ts[0]; //or pass explicitly??? (nein!)
	dx = xs[1]-xs[0]; //or pass explicitly??? (nein!)

	printf("FP: alpha=%.2f, beta=%.2f,gamma=%.2f,theta=%.2f\n",
			alpha, beta, gamma, theta);

	double D =  beta * beta / 2.; //the diffusion coeff
	double dx_sqrd = dx * dx;

	//Set BCs, ICs:
	setICs(Fs, phis, N_phi, xs, num_nodes);
	setBCs(Fs, phis, N_phi, ts, num_steps);

//  e = ones(self._num_nodes() - 1);
//	d_on = D * dt / dx_sqrd;
//	centre_diag = e + d_on;
//	centre_diag[-1] = 1.0;
//	M.setdiag(centre_diag)

	double t_prev, t_next;
	double * U_prev; double * U_next;	double * F_prev; double * F_next;
	double * L_prev; double * RHS;
	int num_active_nodes = num_nodes -1; //Recall that the first node (F[0] is identically zero!!!) only from x_k = 2...N_x are they active
	//TODO: create an array loop for the following:
	U_prev = (double *)malloc(num_active_nodes*sizeof(double));
	U_next = (double *)malloc(num_active_nodes*sizeof(double));
	F_prev = (double *)malloc(num_nodes*sizeof(double)); //!!!
	F_next = (double *)malloc(num_active_nodes*sizeof(double));
	L_prev = (double *)malloc(num_active_nodes*sizeof(double));
	RHS    = (double *)malloc(num_active_nodes*sizeof(double));

    //AllOCATE MASS MTX (diagonals):
	double (* M_l), (*M_c), (*M_u); //lower, central and upper diagonal respectively
	M_l = (double *)malloc(num_active_nodes*sizeof(double));
	M_c = (double *)malloc(num_active_nodes*sizeof(double));
	M_u = (double *)malloc(num_active_nodes*sizeof(double));

	double max_F_next = .0;
	double phi, x_cur; //Uninitialized!
	for (int tk = 1; tk < num_steps; ++tk) {
           t_prev = ts[tk-1];
           t_next = ts[tk];
           for (int phi_idx = 0; phi_idx < N_phi; ++phi_idx) {
        	   phi = phis[phi_idx];

        	   //reload the variables for this time step:
        	   //Rip the previous time solution:
        	   for (int x_idx = 0; x_idx < num_nodes; ++x_idx)
        		   F_prev[x_idx] = Fs[phi_idx][tk-1][x_idx];

			   //Form the advection coefficient:
			   for (int x_idx = 0; x_idx < num_active_nodes; ++x_idx) {
        		   x_cur = xs[x_idx+1];
				   U_prev[x_idx] = -(alpha - x_cur + gamma * sin(theta * (t_prev + phi) ));
				   U_next[x_idx] = -(alpha - x_cur + gamma * sin(theta * (t_next + phi) ));
        	   }

			   //Form operator term at the previous step:
        	   for (int x_idx = 0; x_idx < num_active_nodes-1; ++x_idx) {
        		   L_prev[x_idx] =  U_prev[x_idx] * (F_prev[x_idx+2] - F_prev[x_idx]) / 2. / dx 			//advection
                                  + D * (F_prev[x_idx+2] -  2*F_prev[x_idx+1] + F_prev[x_idx]) / dx_sqrd;   //diffusion

        	   }
        	   //Specifically handle right side conditions:
        	   L_prev[num_active_nodes-1] =   U_prev[num_active_nodes-1]*(F_prev[num_nodes-1] - F_prev[num_nodes-2]) / dx
        			   	   	   	   	   	  + D * (-F_prev[num_nodes-1] + F_prev[num_nodes-2]) / dx_sqrd; //the form of the diffusion term comes from extrapolating the zero Neumann BCs:

        	   //Finally form the RHS:
        	   for (int x_idx = 0; x_idx < num_active_nodes-1; ++x_idx)
        		   RHS[x_idx]= F_prev[x_idx+1] + .5 * dt * L_prev[x_idx];

        	   //and impose the right BCs:
               RHS[num_active_nodes-1] = 0.;

               //Set the MASS MTX:
               //Main diagonal: Carefully read the Thomas Algo index specs!!!
               double d_on  = -D * dt / dx_sqrd;
               double d_off = .5 * D * dt / dx_sqrd;
               double u_factor = .5 * dt / dx / 2.;

               for (int x_idx = 0; x_idx < num_active_nodes-1; ++x_idx) {
            	   //Central diagonal
               		M_c[x_idx] = 1.0 - d_on;
               	   //Lower diagonal: Carefully read the THomas Algo index specs (it only uses the values from M_l[1] onwards !!!
               	   M_l[x_idx+1] = -(d_off - u_factor * U_next[x_idx+1]);
               	   //Upper diagonal: Carefully read the THomas Algo index specs!!!
				   M_u[x_idx]   = -(d_off + u_factor * U_next[x_idx]);
               }
//			  Set the Neumann BCs:
			  M_l[num_active_nodes-1] = -1.0; //
			  M_c[num_active_nodes-1] = 1.0;


               //Thomas Solve it:
               thomasSolve(num_active_nodes, M_l, M_c, M_u, RHS, F_next);

               //Store solution:
               for (int x_idx = 1; x_idx < num_nodes; ++x_idx) {
            	   double lF = F_next[x_idx-1];
            	   max_F_next = fmax(max_F_next, lF);
            	   Fs[phi_idx][tk][x_idx] = lF;
               }
		}//end per-phi loop
//      TODO: Break out of time-loop?
//		if max_F_next< 1e-4:
//			break // from time-loop (remember to set the rest of F to zero!!!
	}//end time loop
}//_solveFP(...)