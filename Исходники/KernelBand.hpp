	void KernelBand<NLSSystemObject>::QuasiNewton(const Eigen::VectorXd& dxi, const Eigen::VectorXd& dfi)
	{
		const double tstart = OpenSMOKE::OpenSMOKEGetCpuTime();

		{
			// The auxiliary vector named x_plus is used here
			Eigen::VectorXd* normSquared = &x_plus_;
			
			normSquared->setZero();
			for (int group = 1; group <= ngroups_; group++)
			{
				for (int j = group - 1; j < static_cast<int>(this->ne_); j += width_)
				{
					int i1 = std::max(0, j - J_->nUpper());
					int i2 = std::min(j + J_->nLower(), static_cast<int>(this->ne_ - 1));

					for (int i = i1; i <= i2; i++)
						(*normSquared)(i) += dxi(j)*dxi(j);
				}
			}

			// The auxiliary vector named x_plus is used here
			Eigen::VectorXd* sum_vector = &f_plus_;

			(*sum_vector) = dfi;

			for (int group = 1; group <= ngroups_; group++)
			{
				for (int j = group - 1; j < static_cast<int>(this->ne_); j += width_)
				{
					double* col_j = BAND_COL(J_, j);
					int i1 = std::max(0, j - J_->nUpper());
					int i2 = std::min(j + J_->nLower(), static_cast<int>(this->ne_ - 1));

					for (int i = i1; i <= i2; i++)
						(*sum_vector)(i) -= BAND_COL_ELEM(col_j, i, j)*dxi(j);
				}
			}

			for (int group = 1; group <= ngroups_; group++)
			{
				for (int j = group - 1; j < static_cast<int>(this->ne_); j += width_)
				{
					double* col_j = BAND_COL(J_, j);
					int i1 = std::max(0, j - J_->nUpper());
					int i2 = std::min(j + J_->nLower(), static_cast<int>(this->ne_ - 1));
				}
			}

			const double eps = 1.e-10;
			for (int j = 0; j < static_cast<int>(this->ne_); j++)
				(*sum_vector)(j) /= ((*normSquared)(j) + eps);

			for (int group = 1; group <= ngroups_; group++)
			{
				for (int j = group - 1; j < static_cast<int>(this->ne_); j += width_)
				{
					double* col_j = BAND_COL(J_, j);
					int i1 = std::max(0, j - J_->nUpper());
					int i2 = std::min(j + J_->nLower(), static_cast<int>(this->ne_ - 1));

					for (int i = i1; i <= i2; i++)
						BAND_COL_ELEM(col_j, i, j) += (*sum_vector)(i)*dxi(j);
				}
			}
		}

		const double tend = OpenSMOKE::OpenSMOKEGetCpuTime();

		numberOfJacobianQuasiAssembling_++;
		cpuTimeSingleJacobianQuasiAssembling_ = tend - tstart;
		cpuTimeJacobianQuasiAssembling_ += cpuTimeSingleJacobianQuasiAssembling_;
	}