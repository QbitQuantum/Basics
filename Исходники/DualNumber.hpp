DualNumber<T> exp(DualNumber<T> x)
{
    using std::exp;
    return DualNumber<T>(exp(x.first), x.second * exp(x.first));
}