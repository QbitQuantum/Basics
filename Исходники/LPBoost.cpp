bool CLPBoost::train(CFeatures* data)
{
	ASSERT(labels);
	ASSERT(features);
	int32_t num_train_labels=labels->get_num_labels();
	int32_t num_feat=features->get_dim_feature_space();
	int32_t num_vec=features->get_num_vectors();

	ASSERT(num_vec==num_train_labels);
	delete[] w;
	w=new float64_t[num_feat];
	memset(w,0,sizeof(float64_t)*num_feat);
	w_dim=num_feat;

	CCplex solver;
	solver.init(E_LINEAR);
	SG_PRINT("setting up lpboost\n");
	solver.setup_lpboost(C1, num_vec);
	SG_PRINT("finished setting up lpboost\n");

	float64_t result=init(num_vec);
	ASSERT(result);

	int32_t num_hypothesis=0;
	CTime time;
	CSignal::clear_cancel();

	while (!(CSignal::cancel_computations()))
	{
		int32_t max_dim=0;
		float64_t violator=find_max_violator(max_dim);
		SG_PRINT("iteration:%06d violator: %10.17f (>1.0) chosen: %d\n", num_hypothesis, violator, max_dim);
		if (violator <= 1.0+epsilon && num_hypothesis>1) //no constraint violated
		{
			SG_PRINT("converged after %d iterations!\n", num_hypothesis);
			break;
		}

		float64_t factor=+1.0;
		if (max_dim>=num_svec)
		{
			factor=-1.0;
			max_dim-=num_svec;
		}

		SGSparseVectorEntry<float64_t>* h=sfeat[max_dim].features;
		int32_t len=sfeat[max_dim].num_feat_entries;
		solver.add_lpboost_constraint(factor, h, len, num_vec, labels);
		solver.optimize(u);
		//CMath::display_vector(u, num_vec, "u");
		num_hypothesis++;

		if (get_max_train_time()>0 && time.cur_time_diff()>get_max_train_time())
			break;
	}
	float64_t* lambda=new float64_t[num_hypothesis];
	solver.optimize(u, lambda);

	//CMath::display_vector(lambda, num_hypothesis, "lambda");
	for (int32_t i=0; i<num_hypothesis; i++)
	{
		int32_t d=dim->get_element(i);
		if (d>=num_svec)
			w[d-num_svec]+=lambda[i];
		else
			w[d]-=lambda[i];

	}
	//solver.write_problem("problem.lp");
	solver.cleanup();

	cleanup();
	
	return true;
}