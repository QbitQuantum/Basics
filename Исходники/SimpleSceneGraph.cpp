	Matrix44 SimpleSceneGraph::calculateRelativeTransform(const Matrix44& absoluteTransform) const
	{
		if (parent == nullptr)
		{
			return absoluteTransform;
		}

		/*
		 * Find the transform for this graph (Gr) relative to the absolute parent transform (Pa) that matches the
		 * absolute transform (Ga) i.e. such that: Ga = Pa * Gr or Gr = Ga * Pa-1
		 */
		Matrix44 inverseParentAbsoluteTransform = parent->getAbsoluteTransform();
		inverseParentAbsoluteTransform.invert();

		return absoluteTransform * inverseParentAbsoluteTransform;
	}