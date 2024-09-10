	void test_block_tridiagonal_solve () {
		// io::parameters <double> params ("../input/block_parameters.txt");
		// omp_set_num_threads(params.nmp);

		int id = process_messenger->get_id ();
		int np = process_messenger->get_np ();
		int n = 60, nrhs = 70, ntop = 0, nbot = 0;
		if (id != 0) {
			ntop = 1;
		}
		if (id != np - 1) {
			nbot = 1;
		}

		std::vector <double> sub (n * nrhs, 0.0);
		std::vector <double> diag (n * nrhs, 0.0);
		std::vector <double> sup (n * nrhs, 0.0);
		std::vector <double> subcopy (n * nrhs, 0.0);
		std::vector <double> diagcopy (n * nrhs, 0.0);
		std::vector <double> supcopy (n * nrhs, 0.0);
		std::vector <double> supsup (n * nrhs, 0.0);
		std::vector <int> ipiv (n * nrhs, 0);

		std::vector <double> x (2 * n * nrhs + 8 * np * nrhs, 0.0);
		std::vector <int> xipiv (2 * np * nrhs, 0);

		std::vector <double> b (n * nrhs, 0.0);
		std::vector <double> bcopy (n * nrhs, 0.0);

		int info;

		srand (1);
		for (int i = 0; i < nrhs; ++i) {
			for (int j = 0; j < n; ++j) {
				sub [i * n + j] = rand () % 100;
				subcopy [i * n + j] = sub [i * n + j];
				diag [i * n + j] = rand () % 100;
				diagcopy [i * n + j] = diag [i * n + j];
				sup [i * n + j] = rand () % 100;
				supcopy [i * n + j] = sup [i * n + j];
				b [i * n + j] = rand () % 100;
				bcopy [i * n + j] = b [i * n + j];
			}
		}
		
		try {
			linalg::block::tridiag_factorize (id, np, n - ntop - nbot, &sub [0], &diag [0], &sup [0], &supsup [0], &ipiv [0], &x [0], &xipiv [0], &info, nrhs);

			linalg::block::tridiag_solve (id, np, n - ntop - nbot,  &sub [0], &diag [0], &sup [0], &supsup [0], &ipiv [0], &b [0], &x [0], &xipiv [0], &info, nrhs);
		} catch (std::exception& except) {
			std::cout << except.what () << '\n';
		}

		for (int j = 0; j < nrhs; ++j) {
			bcopy [j * n] -= diagcopy [j * n] * b [j * n] + supcopy [j * n] * b [1 + j * n];
			for (int i = 1; i < n - 1; ++i) {
				bcopy [i + j * n] -= subcopy [i + j * n] * b [i - 1 + j * n] + diagcopy [i + j * n] * b [i + j * n] + supcopy [i + j * n] * b [i + 1 + j * n];
			}
			bcopy [n - 1 + j * n] -= subcopy [n - 1 + j * n] * b [n - 2 + j * n] + diagcopy [n - 1 + j * n] * b [n - 1 + j * n];
		}
	
		std::vector <double> edge_0 (nrhs), edge_n (nrhs), redge_0 (nrhs), redge_n (nrhs);
	
		for (int i = 0; i < nrhs; ++i) {
			edge_0 [i] = b [i * n];
			edge_n [i] = b [i * n + n - 1];
		}

		if (id != 0) {
			process_messenger->send (nrhs, &edge_0 [0], id - 1, 0);
		}
		if (id != np - 1) {
			process_messenger->recv (nrhs, &redge_n [0], id + 1, 0);
			for (int i = 0; i < nrhs; ++i) {
				bcopy [i * n + n - 1] -= supcopy [i * n + n - 1] * redge_n [i];
			}
		}
		if (id != np - 1) {
			process_messenger->send (nrhs, &edge_n [0], id + 1, 1);
		}
		if (id != 0) {
			process_messenger->recv (nrhs, &redge_0 [0], id - 1, 1);
			for (int i = 0; i < nrhs; ++i) {
				bcopy [i * n] -= subcopy [i * n] * redge_0 [i];
			}
		}
		
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < nrhs; ++j) {
				TSM_ASSERT_DELTA ("Tridiagonal block solver failure", bcopy [j * n + i], 0.0, TEST_TINY);
			}
		}
	}