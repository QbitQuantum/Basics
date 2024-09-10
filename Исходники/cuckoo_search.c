void get_cuckoos(int nnest, int lb[], int ub[], int dim, Nest *best, Nest *new_Nest, Nest *Nests, RngStream g1){

	double beta = 3/2;
	double sigma = pow((tgamma(1.0+beta) * sin(M_PI*beta/2.0) / ((tgamma(1.0+beta)/2.0) * beta * (pow(2.0,((beta-1.0)/2.0))))),(1.0/beta));

	int i;
	for (i = 0; i < nnest; i++){
		int j;
		for (j = 0; j < dim; j++){
			double step = (RngStream_RandU01(g1)*sigma) / pow(fabs(RngStream_RandU01(g1)),(1/beta));
			double stepsize = 0.01 * step * (best->pos[j]);

			new_Nest[i].pos[j] = Nests[i].pos[j] + stepsize * RngStream_RandU01(g1);
		}
		
	}
	simplebounds(nnest, dim, new_Nest, lb, ub);

}