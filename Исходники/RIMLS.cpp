void RIMLS::Fit()
{
	double f = 0;

	Vec3d grad_f(0, 0, 0);
	do 
	{
		int i = 0;
		do 
		{
			double sumW, sumF;
			sumW = sumF = 0;
			Vec3d sumGW, sumGF, sumN;
			sumGW = sumGF = sumN = Vec3d(0.0, 0.0, 0.0);

			for (DataPoint& p : m_neighbors)
			{
				Vec3d px = m_x - p.pos();
				double fx = px.dot(p.normal());

				double alpha = 1.0;
				if (i > 0)
				{
					alpha = exp(-pow((fx - f) / m_sigmaR, 2)) *
						exp(-pow((p.normal() - grad_f).norm() / m_sigmaN, 2));
				}

				double phi = exp(-pow(px.norm() / m_sigmaT, 2));
				double w = alpha*phi;
				Vec3d grad_w = -2.0*alpha*phi*px / pow(m_sigmaT, 2);

				sumW += w;
				sumGW += grad_w;
				sumF += w*fx;
				sumGF += grad_w*fx;
				sumN += w*p.normal();
			}
			f = sumF / sumW;
			grad_f = (sumGF - f*sumGW + sumN) / sumW;
		} while (++i<m_iter && !convergence());

		m_x -= f*grad_f;

	} while ((f*grad_f).norm() > m_threshold);
}