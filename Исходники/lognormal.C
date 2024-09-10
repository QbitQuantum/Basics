Foam::scalar Foam::pdfs::lognormal::sample() const
{

    scalar a = erf((minValue_ - expectation_)/variance_);
    scalar b = erf((maxValue_ - expectation_)/variance_);

    scalar y = rndGen_.scalar01();
    scalar x = erfInv(y*(b - a) + a)*variance_ + expectation_;

    // Note: numerical approximation of the inverse function yields slight
    //       inaccuracies

    x = min(max(exp(x), exp(minValue_)), exp(maxValue_));

    return log(x);
}