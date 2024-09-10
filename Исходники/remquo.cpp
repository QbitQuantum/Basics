	//------------------------------------------------------------------------------
	double Cmath::remquo( double x, double y, int* quo ) // wrapper remquof 
	{
		return (double)remquof( (float)x, (float)y, quo );
	}