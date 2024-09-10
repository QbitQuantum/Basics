/**
 * Simulate
 * 
 * @param		double input
 * @return		double u - control signal
 */
double RegulatorGPC::simulate(double input)
{
	if(m_proces)
	{
		m_w = m_proces->simulate();
		const double y = input;

		m_e = m_w - y;
		m_history_Y.push_front(y);
		m_identify.add_sample(input, m_history_U.front());

		//std::deque<double> A,B;
		m_poly_A.clear();
		m_poly_B.clear();

		//A.push_back(-0.6);
		//B.push_back(0.4);

		m_identify.get_polynomial_a(m_poly_A);
		m_identify.get_polynomial_b(m_poly_B);

		// Return disruption
		if (m_initial_steps_left > 0)
		{
			const double u = m_w - y;
			m_history_U.push_front(u);
			m_initial_steps_left--;
			return u;
		}
    
		// Control algorithm
		// ------------------------------------------------------------------------------------------------------
	
		// 1. Calculating h initial conditions equal zero, delay = 0
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 27
		Eigen::VectorXd h(m_H);
		{
			std::map<std::string, double> others;
			others["k"] = 0;
			others["stationary"] = 0;
			others["noise"] = 0;

			ARX ob;
			ob.set_parameters(m_poly_A,m_poly_B,others);
			for(int i=0; i<m_H; i++)
			{
				h[i] = ob.simulate(1.0);
			}
		}

		// 2. Calculating Q:
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 28
		Eigen::MatrixXd Q;
		Q.setZero(m_H, m_L);
		for(int i=0; i<m_H; i++)
		{
			for(int j=0; j<m_L; j++)
			{
				if(i-j<0)
				{
					Q(i,j) = 0;
				}
				else
				{
					Q(i,j) = h[i-j];
				}
			}
		}

		// 3. Calculating w0
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 8
		Eigen::VectorXd w0(m_H);
		w0[0] = (1-m_alpha)*m_w + m_alpha*y;
		for(int i=1; i<m_H; i++)
		{
			w0[i] = (1-m_alpha)*m_w + m_alpha*w0[i-1];
		}
		

		// 4. Calculating q
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 20
		Eigen::VectorXd tmp;
		tmp.setZero(m_L);
		tmp[0] = 1;
		Eigen::MatrixXd mIdentity;
		mIdentity.setIdentity(m_L,m_L);
		Eigen::VectorXd q = (tmp.transpose()
							*((Q.transpose()*Q + m_ro*mIdentity).inverse())
							*Q.transpose()
							).transpose();

		// 5. Calculating y0
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 31
		Eigen::VectorXd y0(m_H);
		{
			ARX ob;
			std::map<std::string, double> others;
			others["k"] = 0;
			others["stationary"] = 0;
			others["noise"] = 0;
			ob.set_parameters(m_poly_A,m_poly_B,others);
			ob.set_initial_state(m_history_U, m_history_Y);
			ob.simulate(m_history_U.front());
			for (int i=0; i<m_H; i++)
			{
				y0[i] = ob.simulate(m_history_U.front());
			}
		}

		// 6. Calculating final control
		// http://platforma.polsl.pl/rau1/file.php/62/Cz_4_regulacja_predykcyjna.pdf
		// page 35
		const double du = q.transpose() * (w0-y0);
		const double u = m_history_U.front() + du;

		m_history_U.push_front(u);
		return u;
	}
	else
		return 0.0;
}