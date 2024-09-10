inline time::value_type operator - (time const & a, time const & b)
{
    return a.millis_from_midnight() - b.millis_from_midnight();
}