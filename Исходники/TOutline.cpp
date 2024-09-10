	ublas::matrix<double> TOutline::createMatrixForFit(double crX0, double crY0, double crRadius) {
		ublas::matrix<double> data(2,nPoints);
		//double ** data = new2D(2, nPoints, 0.0);
		nPointsMinusCR = 0;
		for (int i=0; i < nPoints; ++i) {
			//drop points from near cornea reflection
			if(_isnan(crRadius) || ((xValues[i] - crX0)*(xValues[i] - crX0) + (yValues[i] - crY0)*(yValues[i] - crY0)
				> crRadius*crRadius)) {

				data(0,nPointsMinusCR) = (double) xValues[i];
				data(1,nPointsMinusCR++) = (double) yValues[i];
			}
		}


		return data;
	}