bool CShareBoost::train_machine(CFeatures* data)
{
	if (data)
		set_features(data);

	if (m_features == NULL)
		SG_ERROR("No features given for training\n")
	if (m_labels == NULL)
		SG_ERROR("No labels given for training\n")

	if (m_nonzero_feas <= 0)
		SG_ERROR("Set a valid (> 0) number of non-zero features to seek before training\n")
	if (m_nonzero_feas >= dynamic_cast<CDenseFeatures<float64_t>*>(m_features)->get_num_features())
		SG_ERROR("It doesn't make sense to use ShareBoost with num non-zero features >= num features in the data\n")

	m_fea = dynamic_cast<CDenseFeatures<float64_t> *>(m_features)->get_feature_matrix();
	m_rho = SGMatrix<float64_t>(m_multiclass_strategy->get_num_classes(), m_fea.num_cols);
	m_rho_norm = SGVector<float64_t>(m_fea.num_cols);
	m_pred = SGMatrix<float64_t>(m_fea.num_cols, m_multiclass_strategy->get_num_classes());
	m_pred.zero();

	m_activeset = SGVector<int32_t>(m_fea.num_rows);
	m_activeset.vlen = 0;

	m_machines->reset_array();
	for (int32_t i=0; i < m_multiclass_strategy->get_num_classes(); ++i)
		m_machines->push_back(new CLinearMachine());

	CTime *timer = new CTime();

	float64_t t_compute_pred = 0; // t of 1st round is 0, since no pred to compute
	for (int32_t t=0; t < m_nonzero_feas; ++t)
	{
		timer->start();
		compute_rho();
		int32_t i_fea = choose_feature();
		m_activeset.vector[m_activeset.vlen] = i_fea;
		m_activeset.vlen += 1;
		float64_t t_choose_feature = timer->cur_time_diff();
		timer->start();
		optimize_coefficients();
		float64_t t_optimize = timer->cur_time_diff();

		SG_SDEBUG(" SB[round %03d]: (%8.4f + %8.4f) sec.\n", t,
				t_compute_pred + t_choose_feature, t_optimize);

		timer->start();
		compute_pred();
		t_compute_pred = timer->cur_time_diff();
	}

	SG_UNREF(timer);

	// release memory
	m_fea = SGMatrix<float64_t>();
	m_rho = SGMatrix<float64_t>();
	m_rho_norm = SGVector<float64_t>();
	m_pred = SGMatrix<float64_t>();

	return true;
}