// Find the smallest and largest values of x and y in fractal
void find_range(double &bottom, double &top, List a){
	for (unsigned int i = 0; i < a.length(); i++){	
		if (top < a.get(i, 0))
			top = a.get(i, 0);
		else if (bottom > a.get(i, 0))
			bottom = a.get(i, 0);
	}
}