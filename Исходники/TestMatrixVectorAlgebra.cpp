	void object::test<6>()
	{
		for (int i = 0;i<10;i++)
		{
			int dim = rand()%1000+2;
			int samplenum1 = rand()%1000+100;
			int samplenum2 = rand()%1000+100;

			Eigen::MatrixXd ha = Eigen::MatrixXd::Random(dim,samplenum1);
			Eigen::MatrixXd hb = Eigen::MatrixXd::Random(dim,samplenum2);



			Eigen::VectorXd haa = (ha.array()*ha.array()).colwise().sum();
			Eigen::VectorXd hbb = (hb.array()*hb.array()).colwise().sum();

			Eigen::MatrixXd hdist = -2*ha.transpose()*hb;

			hdist.colwise() += haa;

			hdist.rowwise() += hbb.transpose();

			
			Matrix<double> ga(ha),gb(hb);

			Matrix<double> gdist = -2*ga.transpose()*gb;

			Vector<double> gaa = (ga.array()*ga.array()).colwise().sum();
			Vector<double> gbb = (gb.array()*gb.array()).colwise().sum();

			gdist.colwise() += gaa;
			gdist.rowwise() += gbb;

			ensure(check_diff(hdist,gdist));
		}
	}