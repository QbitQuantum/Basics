void gravity_fft_p2grid(){
		
	// clean the current density
	for(int i = 0 ; i < root_nx * (root_ny + 2) ; i++) {
		density_r[i] = 0.0;			// density is used to store the surface density
	}
	
	for (int i=0; i<N; i++){
		struct particle p = particles[i];
		// I'm sorry to say I have to keep these traps. Something's wrong if these traps are called.
		
		int x = (int) floor((p.x / boxsize_x + 0.5) * root_nx);
		int y = (int) floor((p.y / boxsize_y + 0.5) * root_ny);
		
		// Formally, pos.x is in the interval [-size/2 , size/2 [. Therefore, x and y should be in [0 , grid_NJ-1]
		
		// xp1, xm1... might be out of bound. They are however the relevant coordinates for the interpolation.

		int xp1 = x + 1;
		int xm1 = x - 1;
		int ym1 = y - 1;
		int yp1 = y + 1;

		
		// Target according to boundary conditions.
		// Although xTarget and yTarget are not relevant here, they will be relevant with shear
		// We have to use all these fancy variables since y depends on x because of the shearing path
		// Any nicer solution is welcome
		
		int xTarget = x;
		int xp1Target = xp1;
		int xm1Target = xm1;
		
		int ym1_xm1Target = (ym1 + root_ny) % root_ny;
		int ym1_xTarget   = ym1_xm1Target;
		int ym1_xp1Target = ym1_xm1Target;
		
		int y_xm1Target = y % root_ny;
		int y_xTarget   = y_xm1Target;
		int y_xp1Target = y_xm1Target;
		
		int yp1_xm1Target = yp1 % root_ny;
		int yp1_xTarget   = yp1_xm1Target;
		int yp1_xp1Target = yp1_xm1Target;
		
		double tx, ty;
		double q0 =  G* p.m /(dx*dy);
		
		// Shearing patch trick
		// This is only an **approximate** mapping
		// one should use an exact interpolation scheme here (Fourier like).
		
		if(xp1Target>=root_nx) {
			xp1Target -= root_nx;							// X periodicity
			y_xp1Target = y_xp1Target + round((shift_shear/boxsize_y) * root_ny);
			y_xp1Target = (y_xp1Target + root_ny) % root_ny;		// Y periodicity
			yp1_xp1Target = yp1_xp1Target + round((shift_shear/boxsize_y) * root_ny);
			yp1_xp1Target = (yp1_xp1Target + root_ny) % root_ny;
			ym1_xp1Target = ym1_xp1Target + round((shift_shear/boxsize_y) * root_ny);
			ym1_xp1Target = (ym1_xp1Target + root_ny) % root_ny;
		}
		
		if(xm1Target<0) {
			xm1Target += root_nx;
			y_xm1Target = y_xm1Target - round((shift_shear/boxsize_x) * root_ny);
			y_xm1Target = (y_xm1Target + root_ny) % root_ny;		// Y periodicity
			yp1_xm1Target = yp1_xm1Target - round((shift_shear/boxsize_x) * root_ny);
			yp1_xm1Target = (yp1_xm1Target + root_ny) % root_ny;
			ym1_xm1Target = ym1_xm1Target - round((shift_shear/boxsize_x) * root_ny);
			ym1_xm1Target = (ym1_xm1Target + root_ny) % root_ny;
		}

		// Distribute density to the 9 nearest cells
		
		tx = ((double)xm1 +0.5) * boxsize_x / root_nx -0.5*boxsize_x - p.x;
		ty = ((double)ym1 +0.5) * boxsize_y / root_ny -0.5*boxsize_y - p.y;
		density_r[(root_ny+2) * xm1Target + ym1_xm1Target] += q0 * W(tx/dx)*W(ty/dy); 

		tx = ((double)x   +0.5) * boxsize_x / root_nx -0.5*boxsize_x - p.x;
		ty = ((double)ym1 +0.5) * boxsize_y / root_ny -0.5*boxsize_y - p.y;
		density_r[(root_ny+2) * xTarget   + ym1_xTarget] += q0 * W(tx/dx)*W(ty/dy); 
		
		tx = ((double)xp1 +0.5) * boxsize_x / root_nx -0.5*boxsize_x - p.x;
		ty = ((double)ym1 +0.5) * boxsize_y / root_ny -0.5*boxsize_y - p.y;
		density_r[(root_ny+2) * xp1Target + ym1_xp1Target] += q0 * W(tx/dx)*W(ty/dy); 

		tx = ((double)xm1 +0.5) * boxsize_x / root_nx -0.5*boxsize_x - p.x;
		ty = ((double)y   +0.5) * boxsize_y / root_ny -0.5*boxsize_y - p.y;
		density_r[(root_ny+2) * xm1Target + y_xm1Target  ] += q0 * W(tx/dx)*W(ty/dy); 

		tx = ((double)x   +0.5) * boxsize_x / root_nx -0.5*boxsize_x - p.x;
		ty = ((double)y   +0.5) * boxsize_y / root_ny -0.5*boxsize_y - p.y;
		density_r[(root_ny+2) * xTarget   + y_xTarget  ] += q0 * W(tx/dx)*W(ty/dy); 

		tx = ((double)xp1 +0.5) * boxsize_x / root_nx -0.5*boxsize_x - p.x;
		ty = ((double)y   +0.5) * boxsize_y / root_ny -0.5*boxsize_y - p.y;
		density_r[(root_ny+2) * xp1Target + y_xp1Target  ] += q0 * W(tx/dx)*W(ty/dy); 

		tx = ((double)xm1 +0.5) * boxsize_x / root_nx -0.5*boxsize_x - p.x;
		ty = ((double)yp1 +0.5) * boxsize_y / root_ny -0.5*boxsize_y - p.y;
		density_r[(root_ny+2) * xm1Target + yp1_xm1Target] += q0 * W(tx/dx)*W(ty/dy); 

		tx = ((double)x   +0.5) * boxsize_x / root_nx -0.5*boxsize_x - p.x;
		ty = ((double)yp1 +0.5) * boxsize_y / root_ny -0.5*boxsize_y - p.y;
		density_r[(root_ny+2) * xTarget   + yp1_xTarget] += q0 * W(tx/dx)*W(ty/dy); 

		tx = ((double)xp1 +0.5) * boxsize_x / root_nx -0.5*boxsize_x - p.x;
		ty = ((double)yp1 +0.5) * boxsize_y / root_ny -0.5*boxsize_y - p.y;
		density_r[(root_ny+2) * xp1Target + yp1_xp1Target] += q0 * W(tx/dx)*W(ty/dy); 
	}
}