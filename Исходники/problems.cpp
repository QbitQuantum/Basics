void createSymmetricProblems
(
	size_t nr_problems,
	Vcl::Core::InterleavedArray<float, 3, 3, -1>& F,
	Vcl::Core::InterleavedArray<float, 3, 3, -1>* R
)
{
	// Random number generator
	std::mt19937_64 rng;
	std::uniform_real_distribution<float> d;
	
	for (int i = 0; i < (int)nr_problems; i++)
	{
		// Rest-state
		Eigen::Matrix3f M;
		M << d(rng), d(rng), d(rng),
		     d(rng), d(rng), d(rng),
		     d(rng), d(rng), d(rng);
		Eigen::Matrix3f MtM = M.transpose() * M;
		F.at<float>(i) = MtM;

		if (R)
		{
			Eigen::Matrix3f Rot;
			Vcl::Mathematics::PolarDecomposition(MtM, Rot, nullptr);
			R->template at<float>(i) = Rot;
		}
	}
}