// Takes 2nd Order tensor in Kelvin representation and returns its
// inverse in Kelvin representation
KVec InvertVector(const KVec& vec)
{
	Eigen::Matrix<double, 3, 3> tens = KelvinVectorToTensor(vec);
	return TensorToKelvinVector(tens.inverse());
}