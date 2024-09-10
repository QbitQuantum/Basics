	double t_E(std::vector<double> n, double f, set_const * C) {
		double res = 0.5 * pow(m_n * m_n * f / C->C_s, 2.0)*C->eta_s(f);

		res += C->U(f);

		int num = n.size();
		/*std::vector<double> nvec;
		for (int i = 0; i < num; i++){
			nvec.push_back(boost::python::extract<double>(n[i]));
		}*/

		double o_sum = 0;
		double r_sum = 0;

		for (int i = 0; i < num; i++){
//			cout << i << ", n[i] = " << n[i] << ", pf = " <<  p_f(n[i]) << endl;
			//res += KineticIntegral(p_f(n[i]), C->M[i] * C->phi_n(C->X_s[i] * f), C);
			res += KineticIntegral(p_f(n[i]), C->M[i] * C->phi_n(C->X_s[i] * (C->M[0]/C->M[i]) * f), C);
			o_sum += C->X_o[i] * n[i];
			r_sum += C->X_r[i] * C->T[i] * n[i];
		}


		res += 0.5 * pow(C->C_o * D * (o_sum) / m_n, 2.0) / (C->eta_o(f));

		res += 0.5 * pow(C->C_r * D * (r_sum) / m_n, 2.0) / (C->eta_r(f));


		//double me = m_e;

		//double pf_e = 0;
		//if (pow(mu_e(n[0] + n[1], n[1], f, C), 2.0) - me*me >= 0){
		//	pf_e = sqrt(pow(mu_e(n[0] + n[1], n[1], f, C), 2.0) - me*me);
		//}

		//if (n[1] != 0.0){
		//	res += KineticIntegral(pf_e, m_e, C);
		//}

		//double mmu = m_mu;
		//double pf_mu = 0;
		//if (pow(mu_e(n[0] + n[1], n[1], f, C), 2.0) - mmu*mmu >= 0){
		//	pf_mu = sqrt(pow(mu_e(n[0] + n[1], n[1], f, C), 2.0) - mmu*mmu);
		//}

		//if (n[1] != 0.0){
		//	res += KineticIntegral(pf_mu, m_mu, C);
		//}

		//gsl_function F;
		//F.function = &func_e;
		//double result = 0.0;
		//double error;
		//double me = m_e;
		//F.params = &me;
		//double pf_e = 0;
		//if (pow(mu_e_2(n[0] + n[1], n[1], f, C), 2.0) - me*me >= 0){
		//	pf_e = sqrt(pow(mu_e_2(n[0] + n[1], n[1], f, C), 2.0) - me*me);
		//}
		////	cout << "MU_E = " <<  mu_e(nn+np, np, f, C) << endl;
		//gsl_integration_qags(&F, 0.0, pf_e, 0, 1e-10, 1000, w_t_E, &result, &error);

		//if (n[1] != 0.0){
		//	//cout << "hey! " << np << endl;
		//	res += result / (pi*pi);
		//}
		////cout << "RESULT   " << result << endl;

		//double mmu = m_mu;
		//F.params = &mmu;
		//double pf_mu = 0;
		//if (pow(mu_e_2(n[0] + n[1], n[1], f, C), 2.0) - mmu*mmu >= 0){
		//	pf_mu = sqrt(pow(mu_e_2(n[0] + n[1], n[1], f, C), 2.0) - mmu*mmu);
		//}
		//gsl_integration_qags(&F, 0.0, pf_mu, 0, 1e-10, 1000, w_t_E, &result, &error);


		//if (n[1] != 0.0){
		//	//cout << "hey! " << np << endl;
		//	res += result / (pi*pi);
		//}

		return res;
	}