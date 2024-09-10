	m3* graphics::getNormalMatrix()
	{
		m4 matrix;
		
		copyMatrix(&matrix, getModelMatrix());
		invert(&matrix);
		transpose(&matrix);
		
		copyMatrix(&normalMatrix, &matrix);
		return &normalMatrix;
	}