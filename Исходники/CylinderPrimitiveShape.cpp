void CylinderPrimitiveShape::SuggestSimplifications(const PointCloud &pc,
	MiscLib::Vector< size_t >::const_iterator begin,
	MiscLib::Vector< size_t >::const_iterator end, float distThresh,
	MiscLib::Vector< MiscLib::RefCountPtr< PrimitiveShape > > *suggestions) const
{
	// sample the bounding box in parameter space at 25 locations
	// these points are used to estimate the other shapes
	// if the shapes succeed the suggestion is returned
	MiscLib::Vector< Vec3f > samples(2 * 25);
	float uStep = (m_extBbox.Max()[0] - m_extBbox.Min()[0]) / 4;
	float vStep = (m_extBbox.Max()[1] - m_extBbox.Min()[1]) / 4;
	float u = m_extBbox.Min()[0];
	for(unsigned int i = 0; i < 5; ++i, u += uStep)
	{
		float v = m_extBbox.Min()[1];
		for(unsigned int j = 0; j < 5; ++j, v += vStep)
			InSpace(u, v * m_cylinder.Radius(), &samples[i * 5 + j],
				&samples[i * 5 + j + 25]);
	}
	size_t c = samples.size() / 2;
	// now check all the shape types
	Sphere sphere;
	if(sphere.Init(samples))
	{
		sphere.LeastSquaresFit(samples.begin(), samples.begin() + c);
		bool failed = false;
		for(size_t i = 0; i < c; ++i)
			if(sphere.Distance(samples[i]) > distThresh)
			{
				failed = true;
				break;
			}
		if(!failed)
		{
			suggestions->push_back(new SpherePrimitiveShape(sphere));
			suggestions->back()->Release();
		}
	}
	Plane plane;
	if(plane.LeastSquaresFit(samples.begin(), samples.begin() + c))
	{
		bool failed = false;
		for(size_t i = 0; i < c; ++i)
			if(plane.Distance(samples[i]) > distThresh)
			{
				failed = true;
				break;
			}
		if(!failed)
		{
			suggestions->push_back(new PlanePrimitiveShape(plane));
			suggestions->back()->Release();
		}
	}
	/*// We suggest a sphere if a curvature of radius along the height
	// does not introduce too large an error
	float length = m_extBbox.Max()[0] - m_extBbox.Min()[0];
	float meanLength = (m_extBbox.Max()[0] + m_extBbox.Min()[0]) / 2;
	float radiusDiff = (std::sqrt(m_cylinder.Radius() * m_cylinder.Radius()
		+ length * length / 4) - m_cylinder.Radius()) / 2;
	float radialExtent = m_extBbox.Max()[1] - m_extBbox.Min()[1];
	if(radiusDiff < distThresh)
	{
		// the center of the sphere is given as the point on the axis
		// with the height of the mean length
		Vec3f center = meanLength * m_cylinder.AxisDirection()
			+ m_cylinder.AxisPosition();
		Sphere sphere(center, m_cylinder.Radius() + radiusDiff);
		suggestions->push_back(new SpherePrimitiveShape(sphere));
		suggestions->back()->Release();
	}

	// We suggest a plane if the mean radius causes only a small error
	// for this we need the angular extent in the curved direction of the cone
	radiusDiff = (m_cylinder.Radius() - std::cos(radialExtent / 2)
		* m_cylinder.Radius()) / 2;
	if(radiusDiff < distThresh)
	{
		GfxTL::Vector2Df bboxCenter;
		m_extBbox.Center(&bboxCenter);
		Vec3f pos, normal;
		InSpace(bboxCenter[0], bboxCenter[1] * m_cylinder.Radius(),
			&pos, &normal);
		// offset position
		pos -= radiusDiff * normal;
		Plane plane(pos, normal);
		suggestions->push_back(new PlanePrimitiveShape(plane));
		suggestions->back()->Release();
	}*/
}