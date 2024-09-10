			double weightedScaling(const Eigen::VectorXf& virtualInput,
					Matrix* scaled, Vector* taui)
			{
				Eigen::VectorXf tauIdeal = BinvIdeal*virtualInput;
				Eigen::VectorXf tmax(tauIdeal.size());

				for (int i=0; i<tmax.size(); ++i)
				{
					tmax(i) = ((tauIdeal(i)>=0)?posDir[i]:fabs(negDir[i]));
				}

				tmax=(tmax/(tmax.minCoeff())).cwiseInverse();

				Eigen::MatrixXf W = tmax.asDiagonal();
				Eigen::MatrixXf Winv = W.inverse();
				Eigen::MatrixXf Binv = Winv*B.transpose()*(B*Winv*B.transpose()).inverse();
				std::cout<<Binv<<std::endl;
				Eigen::VectorXf tdes = Binv*virtualInput;

				double scale_max = 1;
				for (size_t i=0; i<tdes.rows();++i)
				{
					double scale = fabs((tdes(i)>0)?tdes(i)/posDirC[i]:tdes(i)/negDirC[i]);
					if (scale>scale_max) scale_max=scale;
				}
				tdes = tdes/scale_max;
				(*taui) = tdes;
				(*scaled) = B*tdes;

				std::cout<<"Input:"<<virtualInput<<std::endl;
				std::cout<<"Output:"<<*scaled<<std::endl;


				return scale_max;
			}