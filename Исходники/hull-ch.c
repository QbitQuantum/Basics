static double sc(basis_s *v,simplex *s, int k, int j) {
/* amount by which to scale up vector, for reduce_inner */

	double		labound;
	static int	lscale;
	static double	max_scale,
			ldetbound,
			Sb;

	if (j<10) {
		labound = logb(v->sqa)/2;
		max_scale = exact_bits - labound - 0.66*(k-2)-1  -DELIFT;
		if (max_scale<1) {
			warning(-10, overshot exact arithmetic);
			max_scale = 1;

		}

		if (j==0) {
			int	i;
			neighbor *sni;
			basis_s *snib;

			ldetbound = DELIFT;

			Sb = 0;
			for (i=k-1,sni=s->neigh+k-1;i>0;i--,sni--) {
				snib = sni->basis;
				Sb += snib->sqb;
				ldetbound += logb(snib->sqb)/2 + 1;
				ldetbound -= snib->lscale;
			}
		}
	}
	if (ldetbound - v->lscale + logb(v->sqb)/2 + 1 < 0) {
		DEBS(-2)
			DEBTR(-2) DEBEXP(-2, ldetbound)
			print_simplex_f(s, DFILE, &print_neighbor_full);
			print_basis(DFILE,v);
		EDEBS			
		return 0;					
	} else {