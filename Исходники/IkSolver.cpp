void cIKSolver::StepHybrid(const Eigen::MatrixXd& cons_desc, const tProblem& prob, Eigen::MatrixXd& joint_desc,
							Eigen::VectorXd& out_pose)
{
	const int num_dof = cKinTree::GetNumDof(joint_desc);
	const int num_joints = static_cast<int>(joint_desc.rows());
	const int num_cons = static_cast<int>(cons_desc.rows());

	Eigen::VectorXd err;
	Eigen::MatrixXd J;
	Eigen::MatrixXd J_weighted_buff = Eigen::MatrixXd::Zero(num_dof, num_dof);
	Eigen::VectorXd Jt_err_weighted_buff = Eigen::VectorXd::Zero(num_dof);
	Eigen::MatrixXd N = Eigen::MatrixXd::Identity(num_dof, num_dof);
	Eigen::VectorXi chain_joints(num_joints); // keeps track of joints in Ik chain

	double clamp_dist = prob.mClampDist;
	double damp = prob.mDamp;

	int min_priority = std::numeric_limits<int>::max();
	int max_priority = std::numeric_limits<int>::min();

	for (int c = 0; c < num_cons; ++c)
	{
		int curr_priority = static_cast<int>(cons_desc(c, eConsDescPriority));
		min_priority = std::min(min_priority, curr_priority);
		max_priority = std::max(max_priority, curr_priority);
	}

	for (int p = min_priority; p <= max_priority; ++p)
	{
		int curr_num_dof = static_cast<int>(N.cols());
		auto J_weighted = J_weighted_buff.block(0, 0, curr_num_dof, curr_num_dof);
		auto Jt_err_weighted = Jt_err_weighted_buff.block(0, 0, curr_num_dof, 1);

		J_weighted.setZero();
		Jt_err_weighted.setZero();

		chain_joints.setZero();
		
		int num_valid_cons = 0;
		for (int c = 0; c < num_cons; ++c)
		{
			const tConsDesc& curr_cons = cons_desc.row(c);
			int curr_priority = static_cast<int>(curr_cons(eConsDescPriority));

			if (curr_priority == p)
			{
				++num_valid_cons;
				err = BuildErr(joint_desc, out_pose, curr_cons, clamp_dist);
				J = BuildJacob(joint_desc, out_pose, curr_cons);

#if !defined(DISABLE_LINK_SCALE)
				for (int i = 0; i < num_joints; ++i)
				{
					// use entries in the jacobian to figure out if a joint is on the
					// link chain from the root to the constrained end effectors
					// this ignores the root which should not have any scaling
					int scale_idx = gPosDims + num_joints + i;
					int theta_idx = gPosDims + i;
					double scaling = J.col(scale_idx).squaredNorm();
					if (scaling > 0)
					{
						chain_joints(i) = 1;
					}
				}
#endif
				J = J * N;

				double weight = curr_cons(eConsDescWeight);
				J_weighted += weight * J.transpose() * J;
				Jt_err_weighted += weight * J.transpose() * err;
			}
		}

		if (num_valid_cons > 0)
		{
			// apply damping
			// a little more tricky with the null space

			auto N_block = N.block(0, 0, gPosDims + num_joints, N.cols());
			J_weighted += damp * N.transpose() * N;

#if !defined(DISABLE_LINK_SCALE)
			// damp link scaling according to stiffness
			for (int i = 0; i < num_joints; ++i)
			{
				// only scale links that are part of the IK chain
				if (chain_joints(i) == 1)
				{
					int idx = gPosDims + num_joints + i;
					const Eigen::VectorXd& N_row = N.row(idx);

					double d_scale = 1.f - joint_desc(i, cKinTree::eJointDescScale);
					double link_stiffness = joint_desc(i, cKinTree::eJointDescLinkStiffness);
					J_weighted += link_stiffness * N_row * N_row.transpose();
					Jt_err_weighted += link_stiffness * d_scale * N_row;
				}
			}
#endif

			Eigen::VectorXd y = J_weighted.lu().solve(Jt_err_weighted);
			Eigen::VectorXd x = N * y;
			cKinTree::ApplyStep(joint_desc, x, out_pose);
			
			bool is_last = p == max_priority;

			if (!is_last)
			{
				Eigen::MatrixXd cons_mat = Eigen::MatrixXd(num_valid_cons, cons_desc.cols());
				int r = 0;
				for (int c = 0; c < num_cons; ++c)
				{
					const tConsDesc& curr_cons = cons_desc.row(c);
					int curr_priority = static_cast<int>(curr_cons(eConsDescPriority));

					if (curr_priority == p)
					{
						cons_mat.row(r) = curr_cons;
						++r;
					}
				}

				J = BuildJacob(joint_desc, out_pose, cons_mat);
				J = J * N;

				Eigen::MatrixXd curr_N = BuildKernel(J);
				if (curr_N.cols() == 0)
				{
					break;
				}

				N = N * curr_N;
			}
		}
	}
}