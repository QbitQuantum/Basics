float gaussian2d(float A, float c, std::array<float,2> x_0, std::array<float,2> x) {
	return A * expf( (-1.f)*
		( (x[0]-x_0[0])*(x[0]-x_0[0]) + (x[1]-x_0[1])*(x[1]-x_0[1])   ) /  
			(2.f * c*c) );
}