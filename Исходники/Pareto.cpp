void Pareto::from_prior(RNG& rng)
{
	f0 = exp(log(f0_min) + log(f0_max/f0_min)*rng.rand());
	alpha = 1. + 4.*rng.rand();
}