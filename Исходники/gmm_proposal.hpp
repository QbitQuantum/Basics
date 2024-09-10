    void alpha2sd (double alpha,
            double &mu_sd, double &lambda_sd, double &weight_sd) const
    {
        using std::sqrt;

        alpha = alpha < 0.05 ? 0.05 : alpha;
        mu_sd     = 0.15 / alpha;
        lambda_sd = (1 + sqrt(1.0 / alpha)) * 0.15;
        weight_sd = (1 + sqrt(1.0 / alpha)) * 0.2;
    }