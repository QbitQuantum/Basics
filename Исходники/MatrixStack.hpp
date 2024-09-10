	inline void translate(const Nigel::math::Vector4f& direction)
	{
		Nigel::math::Matrix4x4f matrix;
		// Post-multiply the matrix
		*(_matrices.data() + _currentIndex) *= matrix.translation(
				direction.values().x,
				direction.values().y,
				direction.values().z
			);
		// Pre-multiply the inverse matrix by the inverse transformation
		*(_inverseMatrices.data() + _currentIndex) =
			matrix.translation(
				-direction.values().x,
				-direction.values().y,
				-direction.values().z
			)
			*
			(*(_inverseMatrices.data() + _currentIndex));
	}