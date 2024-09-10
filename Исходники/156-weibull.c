double one_weibull(double d, void *params){
    double lambda = apop_data_get(params, 0);
    double k = apop_data_get(params, 1);
    return logl(k) - logl(lambda)
        + (k-1)*(logl(d) - logl(lambda))
        - powl(d/lambda, k);
}