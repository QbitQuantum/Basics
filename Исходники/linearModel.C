		Eigen::VectorXd LinearModel::predict(const vector<double> & substance, bool transform)
		{
			if (training_result_.rows() == 0)
			{
				throw Exception::InconsistentUsage(__FILE__, __LINE__, "Model must be trained before it can predict the activitiy of substances!"); 
			}

			Eigen::VectorXd v = getSubstanceVector(substance, transform); 

			Eigen::VectorXd res = v.transpose()*training_result_;
			//if (offsets_.getSize() == res.getSize()) res -= offsets_; 

			if (transform && y_transformations_.cols() != 0)
			{
				backTransformPrediction(res); 
			}
			
			return res;
		}