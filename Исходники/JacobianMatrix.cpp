		gmtl::Vec3f JacobianMatrix::calculateInverse(const Angle& angle, const gmtl::Vec3f& angular)
		{
			gmtl::Matrix33f matrixJ = calculateJacobian(angle);
	
			//gmtl::Matrix<float, 3, 1> velocityMatrix;
			//velocityMatrix[0][0] = velocity[0];
			//velocityMatrix[1][0] = velocity[1];
			//velocityMatrix[2][0] = velocity[2];

			//gmtl::Matrix<float, 3, 1> solution = matrixJ * velocityMatrix;
			//invert(matrixJ);
			return invert(matrixJ) * angular;//gmtl::Vec3f(solution[0][0], solution[1][0], solution[2][0]);
		}