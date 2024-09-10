TwoBodyJastrowFactor::TwoBodyJastrowFactor (const Eigen::Matrix<real_t, Eigen::Dynamic, Eigen::Dynamic> &correlation_matrix)
    : m_correlation_matrix(correlation_matrix)
{
    // ensure the matrix is square and symmetric
    BOOST_ASSERT(correlation_matrix.rows() == correlation_matrix.cols());
    BOOST_ASSERT(correlation_matrix == correlation_matrix.transpose());
}