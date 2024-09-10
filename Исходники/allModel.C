void ALLModel::calculateXX(Eigen::VectorXd& w, Eigen::MatrixXd& res)
{
    res.resize(descriptor_matrix_.cols(), descriptor_matrix_.cols());
    res.setZero();
    // for all descriptors, calculate their weighted cross-product
    for (int i = 0; i < descriptor_matrix_.cols(); i++)
    {
        for (int j = i; j < descriptor_matrix_.cols(); j++)
        {
            for (int s = 0; s < descriptor_matrix_.rows(); s++)
            {
                res(i, j) += w(s)*descriptor_matrix_(s, i)*descriptor_matrix_(s, j);
            }
            res(j, i) = res(i, j);
        }

    }
}