		// Eigen version
		virtual ReturnValue evaluate()
		{
			CPad* pad = getPad("SqMatrixPad");
			SqMatrix* sqMatrix = (SqMatrix*) pad->getRootObject(sizeof(SqMatrix));

			if (sqMatrix == NULL)
				throwUdxException("Pad does not exist.");

			Eigen::MatrixXd m = Eigen::Map<RMatrixXd>(
				sqMatrix->matrix,
				sqMatrix->dimension,
				sqMatrix->dimension);

			RMatrixXd i = m.inverse();

			Eigen::Map<RMatrixXd>(
				sqMatrix->matrix,
				sqMatrix->dimension,
				sqMatrix->dimension) = i;

			NZ_UDX_RETURN_BOOL(true);
		}