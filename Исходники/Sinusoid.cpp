double Sinusoid::perturb(RNG& rng)
{
    double logH = 0.0;

    int proposal_type = 1;//rng.rand_int(4);

    if(proposal_type == 0)
    {
        // Perturb parameters, changing data along with it
        std::vector<double> mu_old = mu;

        logH += perturb_parameters(rng);
        calculate_mu();

        double n;
        for(size_t i=0; i<N; ++i)
        {
            n = (y[i] - mu_old[i]) / sigma;
            y[i] = mu[i] + sigma * n;
        }

        calculate_logl();
    }
    else if(proposal_type == 1)
    {
        // Perturb parameters, keeping data constant
        // (aka Metropolis step of the posterior!)
        logH -= logl;

        logH += perturb_parameters(rng);

        calculate_mu();
        calculate_logl();

        logH += logl;        
    }
    else if(proposal_type == 2)
    {
        // Just change one datum
        int which = rng.rand_int(N);

        logH -= -0.5*pow((y[which] - mu[which])/sigma, 2);
        y[which] += sigma * rng.randh();
        logH += -0.5*pow((y[which] - mu[which])/sigma, 2);

        calculate_logl();
    }
    else
    {
        // Potentially regenerate many of the data points
        int reps = pow(N, rng.rand());
        int which;
        for(int i=0; i<reps; ++i)
        {
            which = rng.rand_int(N);
            y[which] = mu[which] + sigma * rng.randn();
        }

        calculate_logl();
    }

    return logH;
}