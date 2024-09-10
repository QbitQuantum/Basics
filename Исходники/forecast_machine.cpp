PredStats compute_stats(const vec& obs, const vec& pred)
{
    size_t num_pred = 0;
    double sum_errors = 0;
    double sum_squared_errors = 0;
    double sum_obs = 0;
    double sum_pred = 0;
    double sum_squared_obs = 0;
    double sum_squared_pred = 0;
    double sum_prod = 0;
    size_t same_sign = 0;
    size_t num_vectors = obs.size();
    if(pred.size() < num_vectors)
        num_vectors = pred.size();
    
    for(size_t k = 0; k < num_vectors; ++k)
    {
        if(!std::isnan(obs[k]) && !std::isnan(pred[k]))
        {
            ++ num_pred;
            sum_errors += fabs(obs[k] - pred[k]);
            sum_squared_errors += (obs[k] - pred[k]) * (obs[k] - pred[k]);
            sum_obs += obs[k];
            sum_pred += pred[k];
            sum_squared_obs += obs[k] * obs[k];
            sum_squared_pred += pred[k] * pred[k];
            sum_prod += obs[k] * pred[k];
            if((obs[k] >= 0 && pred[k] >= 0) ||
               (obs[k] <= 0 && pred[k] <= 0))
                ++ same_sign;
        }
    }
    
    PredStats output;
    output.num_pred = num_pred;
    output.rho = (sum_prod * num_pred - sum_obs * sum_pred) /
    sqrt((sum_squared_obs * num_pred - sum_obs * sum_obs) *
        (sum_squared_pred * num_pred - sum_pred * sum_pred));
    output.mae = sum_errors / double(num_pred);
    output.rmse = sqrt(sum_squared_errors / double(num_pred));
    output.perc = double(same_sign) / double(num_pred);
    output.p_val = R::pnorm(atanh(output.rho), 0.0, 1.0 / sqrt(double(output.num_pred-3)), 0.0, 0.0);
    
    return output;
}