// Get the total hamiltonian matrix element between phi1 and phi2
double hamiltonianElement(int N, BasisFunction& phi1, BasisFunction& phi2,
						  Eigen::MatrixXd& R, Eigen::MatrixXd& L2, Eigen::MatrixXd& M,
						  std::vector<double> q, Eigen::MatrixXd& Smat, int s_i, int s_j)
{

	// Construct the double-primed matrices
	Eigen::MatrixXd A_dp, B_dp, C_dp, k_dp;
	A_dp = phi1.getA() + phi2.getA();
	B_dp = phi1.getB() + phi2.getB();
	C_dp = phi1.getC() + phi2.getC();
	k_dp = phi1.getk() + phi2.getk();

	// Diagonalise A''
	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(A_dp);
	Eigen::MatrixXd U = solver.eigenvectors(); // Eigenvectors
	Eigen::MatrixXd D = solver.eigenvalues().asDiagonal(); // Eigenvalues

	// Compute determinant and inverse of A''
	Eigen::MatrixXd D_inv = D;
	double detA_dp = 1.0;
	for (int i = 0; i < N; i++){
		D_inv(i, i) = 1.0/D(i, i);
		detA_dp *= D(i, i);
	}
	Eigen::MatrixXd A_dp_inv = U * D_inv * U.transpose();

	// Calculate overlap integral
	
	double S = overlap(N, A_dp_inv, B_dp, C_dp, R, detA_dp, phi1.getNorm(), phi2.getNorm(),
					   phi1.getJR(), phi2.getJR());
	Smat(s_i, s_j) = S;
	Smat(s_j, s_i) = S;
	
	// Kinetic energy integral
	double T = kinetic(N, phi1.getA(), phi2.getA(), A_dp, A_dp_inv, phi1.getk(), phi2.getk(),  k_dp, S, L2);

	// Drude potential energy integral
	double VD = drudePotential(A_dp_inv, B_dp, R, S, M, N);

	// Now calculate the coulombic potential integrals
	double VC = 0.0;
	double Rij = 0.0;
	std::vector<double> Rij_vec(3);
	
	for (int i = 0; i < N-1; i++){
		Rij_vec[0] = R(i, 0); Rij_vec[1] = R(i, 1); Rij_vec[2] = R(i, 2);
		Rij = R(i, 0)*R(i, 0) + R(i, 1)*R(i, 1) + R(i, 2)*R(i, 2);
		Rij = std::sqrt(Rij);
		
		// Get gi
		double gi =1.0/A_dp_inv(i, i);
		
		for (int j = i+1; j < N; j++){
			// Add the Rij term
			double VC_temp = S/Rij;

			std::vector<double> Pa_vec(3), Pb_vec(3), Pc_vec(3);
			double Pa = 0, Pb = 0, Pc = 0;
			for (int m = 0; m < 3; m++){
				Pa_vec[m] = Rij_vec[m];
				Pb_vec[m] = Rij_vec[m];
				Pc_vec[m] = Rij_vec[m];
				for (int n = 0; n < N; n++){
					Pa_vec[m] += 0.5*A_dp_inv(i, n) * k_dp(n, m);
					Pb_vec[m] -= 0.5*A_dp_inv(j, n) * k_dp(n, m);
					Pc_vec[m] -= 0.5*(A_dp_inv(j, n) - A_dp_inv(i, n))*k_dp(n, m);
				}
				Pa += Pa_vec[m]*Pa_vec[m];
				Pb += Pb_vec[m]*Pb_vec[m];
				Pc += Pc_vec[m]*Pc_vec[m];
			}
			Pa = std::sqrt(Pa);
			Pb = std::sqrt(Pb);
			Pc = std::sqrt(Pc);

			// Get  gj, and gij
			double gj = 1.0/A_dp_inv(j, j);
			double gij = A_dp_inv(i, i) + A_dp_inv(j, j) - 2.0*A_dp_inv(i, j);
			gij = 1.0/gij;

			// Add the aij, bji, cij terms
			VC_temp += coulombPotential(Pc, gij, S);
			VC_temp -= coulombPotential(Pa, gi, S);
			VC_temp -= coulombPotential(Pb, gj, S);

			VC += q[i]*q[j]*VC_temp;
			// Update Rij
			if (j != N-1) { 
				Rij_vec[0] += R(j, 0); Rij_vec[1] += R(j, 1); Rij_vec[2] += R(j, 2);
				double temp = R(j, 0)*R(j, 0) +R(j, 1)*R(j, 1) + R(j, 2)*R(j, 2);
				Rij += std::sqrt(temp);
			}

		}
	}

	double h_el = T + VD + VC;
	
	if (std::isnan(h_el) || std::isinf(h_el)) {  h_el = 0.0; std::cout << "Dodgy hamiltonian element.\n"; }
	
	return h_el;
}