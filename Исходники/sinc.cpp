//------------------------------------------------------------------------
// operator()(float) -
//  evaluate sinc at x, using our table and linear interpolation.
//------------------------------------------------------------------------
float
sinc::operator()(float x) const
{
    using std::abs;
    using std::floor;

    x = abs(x*convfactor_);

    const size_t ix1 = (size_t)floor(x), ix2 = ix1 + 1;
    const float v1 = fetchval(tbl_,ix1), v2 = fetchval(tbl_,ix2);

    return v1 + (x - ix1)*(v2-v1);
}