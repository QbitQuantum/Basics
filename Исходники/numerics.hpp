// unnormalized log( P(alpha|k,n)) for crp
static double lcrpUNormPost(size_t k, size_t n, double alpha)
{
    // sometimes alpha is zero because of floating point error
    // ASSERT_GREATER_THAN_ZERO(std::cout, alpha);
    ASSERT_GREATER_THAN_ZERO(std::cout, n);
    ASSERT_GREATER_THAN_ZERO(std::cout, k);

    return lgamma(alpha)+double(k)*log(alpha)-lgamma(alpha+double(n));
}