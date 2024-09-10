void drwnNNGraphImage::transformNodeFeatures(const drwnFeatureTransform& xform)
{
    vector<double> x, y;
    for (size_t i = 0; i < _nodes.size(); i++) {
        x.resize(_nodes[i].features.rows());
        Eigen::Map<VectorXd>(&x[0], x.size()) = _nodes[i].features.cast<double>();
        xform.transform(x, y);
        _nodes[i].features = Eigen::Map<VectorXd>(&y[0], y.size()).cast<float>();
    }
}