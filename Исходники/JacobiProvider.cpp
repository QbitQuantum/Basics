Eigen::MatrixXf JacobiProvider::computePseudoInverseJacobianMatrix(const Eigen::MatrixXf &m) const
{
#ifdef CHECK_PERFORMANCE
	clock_t startT = clock();
#endif
	MatrixXf pseudo;
	switch (inverseMethod)
	{
	case eTranspose:
		{
			if (jointWeights.rows() == m.cols())
			{
				Eigen::MatrixXf W = jointWeights.asDiagonal();
				Eigen::MatrixXf W_1 = W.inverse();
				pseudo = W_1 * m.transpose() * (m*W_1*m.transpose()).inverse();
			}
			else
			{
				pseudo = m.transpose() * (m*m.transpose()).inverse();
			}
			break;
		}
	case eSVD:
		{
				 float pinvtoler = 0.00001f;
				 pseudo = MathTools::getPseudoInverse(m, pinvtoler);
				 break;
		}
	case eSVDDamped:
		{
				 float pinvtoler = 0.00001f;
				 pseudo = MathTools::getPseudoInverseDamped(m,pinvtoler);
				 break;
		}
	default:
		THROW_VR_EXCEPTION("Inverse Jacobi Method nyi...");
	}
#ifdef CHECK_PERFORMANCE
	clock_t endT = clock();
	float diffClock = (float)(((float)(endT - startT) / (float)CLOCKS_PER_SEC) * 1000.0f);
	//if (diffClock>10.0f)
	cout << "Inverse Jacobi time:" << diffClock << endl;
#endif
	return pseudo;
}