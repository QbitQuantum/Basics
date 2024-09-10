void CLogistic::TrainOnevsAll(const Matrix<double, Dynamic, Dynamic, RowMajor>& X, const VectorXd& y_class, int num_labels, double lambda)
{
	/*
		trains multiple logistic regression classifiers and returns all
		the classifiers in a matrix classifier, where the i-th row of classifier 
		corresponds to the classifier for label i
	*/

	int m = X.rows();
	int n = X.cols();
	classifier = Matrix<double, Dynamic, Dynamic, RowMajor>::Zero(num_labels, n);

	// Iterate through all the classification classes
	for(int class_ndx = 0; class_ndx < num_labels; class_ndx++)
	{
		VectorXd theta  = VectorXd::Zero(n);

		// classify one vs. all
		VectorXd c = VectorXd::Zero(y_class.rows());
		for (int point_ndx = 0; point_ndx < y_class.rows(); point_ndx++)
			c(class_ndx) = (y_class(point_ndx) == class_ndx ? 1.0 : .0);

		GradientDescent(X, c, theta, lambda);

		// store the result inside classifier
		classifier.row(class_ndx) = theta.transpose();
	}
}