	/**
	 * invert the matrix
	 */
	Matrix<M, N> inversed(void) const {
#ifdef CONFIG_ARCH_ARM
		Matrix<M, N> res;
		arm_mat_inverse_f32(&this->arm_mat, &res.arm_mat);
		return res;
#else
		Eigen::Matrix<float, M, N, Eigen::RowMajor> Me = Eigen::Map<Eigen::Matrix<float, M, N, Eigen::RowMajor> >
				(this->arm_mat.pData);
		Eigen::Matrix<float, M, N, Eigen::RowMajor> MyInverse = Me.inverse(); //not sure if A = A.inverse() is a good idea
		Matrix<M, N> res(MyInverse.data());
		return res;
#endif
	}