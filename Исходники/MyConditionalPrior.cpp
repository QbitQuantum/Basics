void MyConditionalPrior::from_prior(RNG& rng)
{
    location_log_period = cauchy.generate(rng);
    scale_log_period = 5*rng.rand();

    location_log_amplitude = cauchy.generate(rng);
    scale_log_amplitude = 5*rng.rand();
}