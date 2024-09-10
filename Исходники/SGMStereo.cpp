void SGMStereo::addPixelwiseHamming(const int* leftCensusRow, const int* rightCensusRow) {
	for (int x = 0; x < disparityTotal_; ++x) {
		int leftCencusCode = leftCensusRow[x];
		int hammingDistance = 0;
		for (int d = 0; d <= x; ++d) {
			int rightCensusCode = rightCensusRow[x - d];
			hammingDistance = static_cast<int>(_mm_popcnt_u32(static_cast<unsigned int>(leftCencusCode^rightCensusCode)));
			pixelwiseCostRow_[disparityTotal_*x + d] += static_cast<unsigned char>(hammingDistance*censusWeightFactor_);
		}
		hammingDistance = static_cast<unsigned char>(hammingDistance*censusWeightFactor_);
		for (int d = x + 1; d < disparityTotal_; ++d) {
			pixelwiseCostRow_[disparityTotal_*x + d] += hammingDistance;
		}
	}
	for (int x = disparityTotal_; x < width_; ++x) {
		int leftCencusCode = leftCensusRow[x];
		for (int d = 0; d < disparityTotal_; ++d) {
			int rightCensusCode = rightCensusRow[x - d];
			int hammingDistance = static_cast<int>(_mm_popcnt_u32(static_cast<unsigned int>(leftCencusCode^rightCensusCode)));
			pixelwiseCostRow_[disparityTotal_*x + d] += static_cast<unsigned char>(hammingDistance*censusWeightFactor_);
		}
	}
}