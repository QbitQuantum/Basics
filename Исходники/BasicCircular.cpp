void BasicCircular::from_prior(RNG& rng)
{
	xc = x_min + (x_max - x_min)*rng.rand();
	yc = y_min + (y_max - y_min)*rng.rand();
	width = exp(log(1E-2*size) + log(1E3)*rng.rand());

	mu = exp(log(mu_min) + log(mu_max/mu_min)*rng.rand());
}