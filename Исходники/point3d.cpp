	void Point3D::optimize(const size_t n_iter)
	{
		Vector3d old_point = pos_;
		double chi2 = 0.0;
		Matrix3d A;
		Vector3d b;

		for (size_t i = 0; i < n_iter; i++)
		{
			A.setZero();
			b.setZero();
			double new_chi2 = 0.0;

			// 计算残差
			for (auto it = obs_.begin(); it != obs_.end(); ++it)
			{
				Matrix23d J;
				const Vector3d p_in_f((*it)->frame->T_f_w_ * pos_);
				Point3D::jacobian_xyz2uv(p_in_f, (*it)->frame->T_f_w_.rotation_matrix(), J);
				const Vector2d e(project2d((*it)->f) - project2d(p_in_f));
				new_chi2 += e.squaredNorm();
				A.noalias() += J.transpose() * J;
				b.noalias() -= J.transpose() * e;
			}

			// 求解线性系统
			const Vector3d dp(A.ldlt().solve(b));

			// 检测误差有没有增长
			if ((i > 0 && new_chi2 > chi2) || (bool)std::isnan((double)dp[0]))
			{
				pos_ = old_point; // 回滚
				break;
			}

			// 更新模型
			Vector3d new_point = pos_ + dp;
			old_point = pos_;
			pos_ = new_point;
			chi2 = new_chi2;

			// 收敛则停止
			if (norm_max(dp) <= EPS)
				break;
		}

	}