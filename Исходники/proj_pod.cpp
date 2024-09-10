ProjPOD& ProjPOD::Find( const DataSystem& data ) {

	size_t totalPoints = 0;
	for(uint32_t i=0;i<data.numParameters;++i)
		totalPoints += data.dataSets[i].points.size();

	MatrixXd dataMatrix;
	dataMatrix.setZero( data.dimension, totalPoints );

	size_t k = 0;
	for(uint32_t i=0;i<data.numParameters;++i)
		for(size_t j=0;j<data.dataSets[i].points.size();++j)
			dataMatrix.col(k++) = data.dataSets[i].points[j];

	JacobiSVD<MatrixXd> svd(dataMatrix,ComputeThinU);
	singularValues = svd.singularValues();

	W = svd.matrixU().leftCols(targetDimension);
	return *this;
}