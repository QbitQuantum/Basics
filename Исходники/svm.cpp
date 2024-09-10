/// Find the plan parameters by computing the Lagrangian coefficients by solving for the 
/// quadratic program
Eigen::Vector3d lagrangian () {

	bool dbg = 0;

	// Create the cost function
	int N = data.size();
	double H_ [N * N], f_ [N];
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) 
			H_[i * N + j] = data[i].second * data[j].second * data[i].first.dot(data[j].first);
		f_[i] = -1.0;
		H_[i * (N+1)] += 1e-8;
	}
	QuadProgPP::Matrix <double> H (&(H_[0]), N, N);
	QuadProgPP::Vector <double> f (&(f_[0]), N);
	if(dbg) cout << "H: " << H << endl;
	if(dbg) cout << "f: " << f << endl;

	// Create the inequality constraints (alpha_i >= 0)
	double I_ [N * N], i0_ [N];
	for(int i = 0; i < N; i++) {
		I_[i * (N+1)] = 1.0;
		i0_[i] = 0.0;
	}
	QuadProgPP::Matrix <double> I (&(I_[0]), N, N);
	QuadProgPP::Vector <double> i0 (&(i0_[0]), N);
	if(dbg) cout << "I: " << I << endl;
	if(dbg) cout << "i0: " << i0 << endl;

	// Create the equality constraint ((sum_i alpha_i * y_i) = 0)
	double E_ [N], e0_ [1];
	for(int i = 0; i < N; i++) E_[i] = data[i].second;
	e0_[0] = 0.0;
	QuadProgPP::Matrix <double> E (&(E_[0]), N, 1);
	QuadProgPP::Vector <double> e0 (&(e0_[0]), 1);
	if(dbg) cout << "E: " << E << endl;
	if(dbg) cout << "e0: " << e0 << endl;

	// Solve the problem
	QuadProgPP::Vector <double> x;
	solve_quadprog(H, f, E, e0, I, i0, x);
	if(dbg) cout << "x: " << x << endl;

	// Compute the line direction 
	Eigen::Vector2d w (0, 0);
	Eigen::VectorXd x_ (N), y(N);
	for(int i = 0; i < N; i++) {
		w += x[i] * data[i].second * data[i].first;
		x_(i) = x[i];
		y(i) = data[i].second;
	}
	if(dbg) cout << "w: " << w.transpose() << endl;

	// Compute the line intersection
	int minPos;
	for(int i = 0; i < N; i++) {
		if((x[i] > 0.1) && (data[i].second > 0)) {
			minPos = i;
			break;
		}
	}
	Eigen::MatrixXd X (N,2), G(N,N);
	for(int i = 0; i < N; i++) X.row(i) = data[i].first;
	G = X * X.transpose();
	double b = 1 - (G.row(minPos) * (x_.cwiseProduct(y)));
	if(dbg) printf("b: %lf\n", b);

	return Eigen::Vector3d(w(0), w(1), b);
}