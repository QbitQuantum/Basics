	double splEval(NumericVector xnew){
		gsl_set_error_handler_off();
		int Nx1 = x1.length(), Nx2 = x2.length(), Nx3 = x3.length();
		int x3_index = findInterval1(xnew(2), x3);		//Find which discrete value it is in the 3rd dimension; 
		NumericVector y2(Nx2);
		
		// Interpolate the first dimension conditional the other values; 
		for(int j=0; j<Nx2; j++){
			y2(j) = spl_vec[(x3_index-1)*Nx2+j].splEval(xnew(0));
		}
		
		// Set up another spl object for the 2nd dimension; 
		struct spl spl2 = spl_init(x2, y2);
		double out = spl2.splEval(xnew(1));
		spl2.splfree();
		return(out);		
	}