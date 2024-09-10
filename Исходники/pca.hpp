DenseMatrix project(const DenseMatrix& projection_matrix, const DenseVector& mean_vector,
                    RandomAccessIterator begin, RandomAccessIterator end, 
                    FeatureVectorCallback callback, IndexType dimension)
{
	timed_context context("Data projection");

	DenseVector current_vector(dimension);
	DenseVector current_vector_subtracted_mean(dimension);

	DenseMatrix embedding = DenseMatrix::Zero((end-begin),projection_matrix.cols());

	for (RandomAccessIterator iter=begin; iter!=end; ++iter)
	{
		callback(*iter,current_vector);
		current_vector_subtracted_mean = current_vector - mean_vector;
		embedding.row(iter-begin) = projection_matrix.transpose()*current_vector_subtracted_mean;
	}

	return embedding;
}