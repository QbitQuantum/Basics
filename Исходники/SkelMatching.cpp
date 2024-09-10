void Dist_grad(const Eigen::Matrix<double,Eigen::Dynamic,1> &t,
			   const std::vector<skeleton::BranchContProjSkel::Ptr> &skel,
			   double &value,
			   Eigen::Matrix<double,Eigen::Dynamic,1> &gradient)
{
	Eigen::Matrix4d A = Eigen::Matrix4d::Zero();
	Eigen::Vector4d b = Eigen::Vector4d::Zero();
	value = 0.0;
	gradient = Eigen::Matrix<double,Eigen::Dynamic,1>::Zero(t.rows(),1);

	std::vector<Eigen::Vector4d> ori(skel.size());
	std::vector<Eigen::Vector4d> vec(skel.size());
	std::vector<Eigen::Vector4d> orijac(skel.size());
	std::vector<Eigen::Vector4d> vecjac(skel.size());
	std::vector<Eigen::Matrix4d> A_part_jac(skel.size());
	std::vector<Eigen::Vector4d> b_part_jac(skel.size());

	for(unsigned int i=0;i<skel.size();i++)
	{
		Compositor<Application<Eigen::Matrix<double,8,1>,Eigen::Vector3d>,Application<Eigen::Vector3d,double> >
			fun(skel[i]->getModel()->getR8Fun(),skel[i]->getCompFun());
		Eigen::Matrix<double,8,1> veclin = fun(t(i));
		Eigen::Matrix<double,8,1> jaclin = fun.jac(t(i));

		ori[i]  = veclin.block<4,1>(0,0);
		vec[i]  = veclin.block<4,1>(4,0).normalized();

		orijac[i] = jaclin.block<4,1>(0,0);
		vecjac[i] = jaclin.block<4,1>(4,0)*(1.0/veclin.block<4,1>(4,0).norm());

		Eigen::Matrix4d A_part = Eigen::Matrix4d::Identity() - vec[i]*vec[i].transpose();
		Eigen::Vector4d b_part = A_part*ori[i];

		A_part_jac[i] = - vecjac[i]*vec[i].transpose() - vec[i]*vecjac[i].transpose();
		b_part_jac[i] = A_part_jac[i] * ori[i] + A_part * orijac[i];

		A+=A_part;
		b+=b_part;
	}

	Eigen::Matrix4d A_inv = A.inverse();

	Eigen::Vector4d P = A_inv*b;
	for(unsigned int i=0;i<skel.size();i++)
	{
		Eigen::Vector4d P_jac = A_inv * A_part_jac[i] * P + A_inv * b_part_jac[i];

		double Dist = (P - ori[i]).squaredNorm() - pow((P - ori[i]).dot(vec[i]),2);

		gradient(i) =  2*(P_jac - orijac[i]).dot(P - ori[i])
					  -2*(P_jac - orijac[i]).dot(vec[i]) * (P - ori[i]).dot(vec[i])
					  -2*(P - ori[i]).dot(vecjac[i]) * (P - ori[i]).dot(vec[i]);

		value += Dist;
	}
}