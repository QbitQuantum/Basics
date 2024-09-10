void FubiGMR::calculateGMR(std::vector<Fubi::Vec3f>& means, std::vector<Fubi::Matrix3f>& inverseCovs)
{
	// Helping vars for extracting the right columns (t, x, y, z)
	int outDataSize = means.size();
	const int outDim = 3;
	Vector inComponents(1), outComponents(outDim);
	inComponents(0) = 0;
	for (unsigned int i = 0; i < 3; i++)
		outComponents(i) = (float)(i + 1);
	Matrix inData(outDataSize, 1);
	float* inArray = inData.Array();
	for (int i = 0; i < outDataSize; ++i)
	{
		inArray[i] = (float)i;
	}

	// Calculate probabilites for each data point
	Matrix Pxi(outDataSize, m_numStates);
	for (int i = 0; i < outDataSize; i++)
	{
		float norm_f = 0.0f;
		Vector row;
		for (int s = 0; s < m_numStates; s++)
		{
			float p_i = m_priors[s] * pdfState(inData.GetRow(i, row), inComponents, s);
			Pxi(i, s) = p_i;
			norm_f += p_i;
		}
		Pxi.SetRow(Pxi.GetRow(i) / norm_f, i);
	}

	// Calculate sigmas + variance for each state
	Matrix* subSigma = new Matrix[m_numStates];
	Matrix* subSigmaVar = new Matrix[m_numStates];
	for (int s = 0; s < m_numStates; s++)
	{
		Matrix isubSigmaIn;
		Matrix subSigmaOut;
		m_sigma[s].GetMatrixSpace(inComponents, inComponents, subSigmaOut);
		subSigmaOut.Inverse(isubSigmaIn);
		m_sigma[s].GetMatrixSpace(outComponents, inComponents, subSigmaOut);
		subSigma[s] = subSigmaOut*isubSigmaIn;
		m_sigma[s].GetMatrixSpace(outComponents, outComponents, subSigmaOut);
		m_sigma[s].GetMatrixSpace(inComponents, outComponents, isubSigmaIn);
		subSigmaVar[s] = subSigmaOut - subSigma[s] * isubSigmaIn;
	}

	// Now calculate the final mus and sigmas for each data point
	Matrix subMuIn;
	Matrix subMuOut;
	m_mu->GetColumnSpace(outComponents, subMuOut);
	m_mu->GetColumnSpace(inComponents, subMuIn);
	for (int i = 0; i < outDataSize; i++)
	{
		// Calculate mu and sigma for the current data point
		Matrix sigmaOut(outDim, outDim);
		Vector muOut(outDim, true);
		for (int s = 0; s < m_numStates; s++)
		{
			const float pIS = Pxi(i, s);
			muOut += (subMuOut.GetRow(s) + (subSigma[s] * (inData.GetRow(i) - subMuIn.GetRow(s)))) * pIS;
			sigmaOut += subSigmaVar[s] * (pIS*pIS);
		}

		// Copy them to the output vars
		Fubi::Matrix3f& inverseCov = inverseCovs[i];
		Fubi::Vec3f& mean = means[i];
		for (unsigned int j = 0; j < outDim; j++)
		{
			mean[j] = muOut[j];
			for (unsigned int k = 0; k < outDim; k++)
				inverseCov.c[j][k] = sigmaOut(j, k);
		}
		// Don't forget to invert the covariance matrix!
		inverseCov = inverseCov.inverted();
	}

	delete[] subSigma;
	delete[] subSigmaVar;
}