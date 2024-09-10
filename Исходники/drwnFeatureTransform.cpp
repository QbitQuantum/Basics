void drwnFeatureTransform::transform(const vector<vector<double> >& x,
    vector<vector<double> >& y, const drwnFeatureTransform& xform) const
{
    y.resize(x.size());
    vector<double> z;
    for (unsigned i = 0; i < x.size(); i++) {
        xform.transform(x[i], z);
        this->transform(z, y[i]);
    }
}