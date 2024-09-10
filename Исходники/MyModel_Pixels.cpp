void MyModel_Pixels::from_prior(DNest4::RNG& rng)
{
    for(size_t j=0; j<nj; ++j)
        for(size_t i=0; i<ni; ++i)
            n(i, j) = rng.randn();

    sd = rng.rand();

    DNest4::Cauchy c1(0.0, 1.0);
    x0 = -std::abs(c1.generate(rng));

    DNest4::Cauchy c2(0.0, 0.1*data.get_t_range());
    timescale = std::abs(c2.generate(rng));

    calculate_obscurer_map();
}