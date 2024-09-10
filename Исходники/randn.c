// Gauss random number cumulative distribution function
float randnf_cdf(float _x,
                 float _eta,
                 float _sig)
{
    return 0.5 + 0.5*erff( M_SQRT1_2*(_x-_eta)/_sig );
}