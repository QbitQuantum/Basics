void JF12Field::randomStriated(int seed) {
	useStriated = true;
	int N = 100;
	striatedGrid = new ScalarGrid(Vector3d(0.), N, 0.1 * kpc);

	Random random;
	if (seed != 0)
		random.seed(seed);

	for (int ix = 0; ix < N; ix++)
		for (int iy = 0; iy < N; iy++)
			for (int iz = 0; iz < N; iz++) {
				float &f = striatedGrid->get(ix, iy, iz);
				f = round(random.rand()) * 2 - 1;
			}
}