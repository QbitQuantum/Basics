		double log_like(VectorType arg_vec){

			return - arg_vec.dot(arg_vec);
		}