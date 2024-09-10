double compute_likelihood(document* doc, lda_model* model, double** phi, double* var_gamma) {
	double likelihood = 0, digsum = 0, var_gamma_sum = 0, dig[model->num_topics];
	int k = 0, n = 0, index = 0;
  memset(dig,0.0,sizeof(dig));

	for (k = 0; k < model->num_topics; k++)
	{
		dig[k] = digamma(var_gamma[k]);
		var_gamma_sum += var_gamma[k];
	}
	digsum = digamma(var_gamma_sum);

	likelihood = lgamma(model->alpha * model->num_topics) -
               model->num_topics *
               lgamma(model->alpha) -
               lgamma(var_gamma_sum);

	for (k = 0; k < model->num_topics; k++)
	{
		likelihood += (model->alpha - 1)*(dig[k] - digsum) + lgamma(var_gamma[k]) - (var_gamma[k] - 1)*(dig[k] - digsum);

		for (n = 0; n < doc->length; n++)
		{
			if (phi[n][k] > 0)
			{
        index = doc->words[n];
				likelihood += doc->counts[n]*
					(phi[n][k]*((dig[k] - digsum) - log(phi[n][k])
					+ model->log_prob_w[k][index]));
			}
		}
	}
	return(likelihood);
}