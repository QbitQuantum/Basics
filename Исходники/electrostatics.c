void electric_field(struct Structure This_Structure, float grid_span, int grid_size, fftw_real * grid, int *shared_x, struct atom_values *atoms, int natoms_in)
{

/************/

	/* Counters */

	int residue, atom, i;

	/* Co-ordinates */

	int x, y, z;
	float x_centre, y_centre, z_centre;

	/* Variables */

	float distance;
	float phi, epsilon;

	while (1) {
		
		pthread_mutex_lock(&shared_x_mutex);
		x = *shared_x;
		*shared_x = *shared_x + 1;
		pthread_mutex_unlock(&shared_x_mutex);
		
		if (x >= grid_size)
			break;
		
		printf(".");

		x_centre = gcentre(x, grid_span, grid_size);
		__mtype mx_centre = _set1_ps(x_centre);

		for (y = 0; y < grid_size; y++) {

			y_centre = gcentre(y, grid_span, grid_size);
			__mtype my_centre = _set1_ps(y_centre);

			for (z = 0; z < grid_size; z++) {

				z_centre = gcentre(z, grid_span, grid_size);
				__mtype mz_centre = _set1_ps(z_centre);

				phi = 0;
				__mtype phis = _set1_ps(0.0);
				
				for (i = 0; i < natoms_in; i++) {
				
					__mtype xs = _load_ps(atoms[i].xs);
					__mtype ys = _load_ps(atoms[i].ys);
					__mtype zs = _load_ps(atoms[i].zs);
					__mtype charges = _load_ps(atoms[i].charges);
					__mtype distances;
					
					// Calculo distancias (el original pythagoras)
					__mtype diffxs = _sub_ps(xs, mx_centre);
					__mtype diffys = _sub_ps(ys, my_centre);
					__mtype diffzs = _sub_ps(zs, mz_centre);
					
					diffxs = _mul_ps(diffxs, diffxs);
					diffys = _mul_ps(diffys, diffys);
					diffzs = _mul_ps(diffzs, diffzs);
					
					distances = _add_ps(diffxs, diffys);
					distances = _add_ps(distances, diffzs);
					
					distances = _sqrt_ps(distances);
					
					// A partir de aquí implemento los if's originales usando solo máscaras de bits
					
					// Trunco a 2 como mínimo
					distances = _max_ps(distances, _set1_ps(2.0));
					
					__mtype epsilons = _set1_ps(0.0);
					__mtype tmp;
					__mtype tmp2;
					
					// if >= 8
					tmp = _cmpge_ps(distances, _set1_ps(8.0));
					epsilons = _and_ps(tmp, _set1_ps(80.0));
					
					// else if <= 6
					tmp = _cmple_ps(distances, _set1_ps(6.0));
					tmp = _and_ps(tmp, _set1_ps(4.0));
					epsilons = _or_ps(epsilons, tmp);
					
					// else
					tmp = _cmpgt_ps(distances, _set1_ps(6.0));
					tmp2 = _cmpeq_ps(epsilons, _set1_ps(0.0));
					tmp = _and_ps(tmp, tmp2);
					tmp2 = _mul_ps(distances, _set1_ps(38.0));
					tmp2 = _sub_ps(tmp2, _set1_ps(224.0));
					tmp = _and_ps(tmp, tmp2);
			
					// Valor final
					epsilons = _or_ps(epsilons, tmp);
					
					// Calculo las phis
					tmp = _mul_ps(epsilons, distances);
					tmp = _div_ps(charges, tmp);
					
					// Acumulo las phis
					phis = _add_ps(phis, tmp);
				}
				#ifdef USE_AVX
				
				phis = _mm256_hadd_ps(phis, phis);
				phis = _mm256_hadd_ps(phis, phis);
				
				phi = phis[0] + phis[4];
				
				#else
				
				float tmp, tmp2;
				
				tmp = phis[0] + phis[1];
				tmp2 = phis[2] + phis[3];
				
				phi = tmp + tmp2;
				
				#endif
				grid[gaddress(x, y, z, grid_size)] = (fftw_real) phi;

			}
		}
	}

/************/

	return;

}