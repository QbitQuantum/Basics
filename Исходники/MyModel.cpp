void MyModel::from_prior(RNG& rng)
{
	objects.from_prior(rng);
	calculate_image();
	sigma = exp(log(1.) + log(1E6)*rng.rand());
}