/**
 * @brief Fills a matrix with random (but symmetric, positive definite) values
 */
void createRandom(MatrixXd& tgt, size_t rank)
{
	assert(tgt.rows() == tgt.cols());
	VectorXd tmp(tgt.rows());
	tgt.setZero();

	for(size_t ii=0; ii<rank; ii++) {
		tmp.setRandom();
		tmp.normalize();
		tgt += tmp*tmp.transpose();
	}
}