/**
* \ingroup GLVisualization
* Apply the computed rotation matrix
* This method must be invoked inside the \code glutDisplayFunc() \endcode
*
**/
void Arcball::applyRotationMatrix()
{
	glMultMatrixf(startMatrix);

	if (isRotating)
	{  // Do some rotation according to start and current rotation vectors
	   //cerr << currentRotationVector.transpose() << " " << startRotationVector.transpose() << endl;
		if ((currentRotationVector - startRotationVector).norm() > 1E-6)
		{
			Eigen::Vector3d rotationAxis = currentRotationVector.cross(startRotationVector);
			

			Eigen::Matrix3d currentMatrix;
			for (int i = 0; i < 3;i++) {
				for (int j = 0; j < 3;j++) {
					currentMatrix(i, j) = (double)startMatrix[4 * i + j];
				}
			}
			
			rotationAxis = currentMatrix*rotationAxis;// linear transformation
			
			rotationAxis.normalize();

			double val = currentRotationVector.dot(startRotationVector);
			val > (1 - 1E-10) ? val = 1.0 : val = val;
			double rotationAngle = acos(val) * 180.0f / (float)M_PI;//unit vector 

																	// rotate around the current position
			
			glRotatef(rotationAngle * 2, -rotationAxis.x(), -rotationAxis.y(), -rotationAxis.z());
			
		}
	}
	
}