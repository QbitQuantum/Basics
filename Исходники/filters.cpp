void Filter::init(const Vector &y0)
{
    // if there is a last input then take it as guess for the next input
    if (uold[0].size()>0)
        init(y0,uold[0]);
    else    // otherwise use zero
        init(y0,zeros(y0.length()));
}