float LinearSvmModel::compute_score(const Eigen::VectorXf &feature_vector) const
{
    assert(w.size() > 0);
    return feature_vector.dot(w) - bias;
}