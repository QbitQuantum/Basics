void ConePrimitiveShape::SuggestSimplifications(const PointCloud &pc,
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
		{
			float bmpu, bmpv;
			if(m_cone.Angle() >= M_PI / 4)
			{
				bmpu = std::sin(v) * u;
				bmpv = std::cos(v) * u;
			}
			else
			{
				bmpu = u;
				float r = m_cone.RadiusAtLength(u);
				bmpv = (v - float(M_PI)) * r;
			}
			InSpace(bmpu, bmpv, &samples[i * 5 + j],
				&samples[i * 5 + j + 25]);
		}
	}
	size_t c = samples.size() / 2;
	// now check all the shape types
	Cylinder cylinder;
	if(cylinder.InitAverage(samples))
	{
		cylinder.LeastSquaresFit(samples.begin(), samples.begin() + c);
		bool failed = false;
		for(size_t i = 0; i < c; ++i)
			if(cylinder.Distance(samples[i]) > distThresh)
			{
				failed = true;
				break;
			}
		if(!failed)
		{
			suggestions->push_back(new CylinderPrimitiveShape(cylinder));
			suggestions->back()->Release();
		}
	}
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

	/*// simpler shapes are suggested if the maximal curvature of the cone
	// is small compared to the extend in relation to the distThresh

	float meanRadius, length, meanLength, radialExtent;
	// the cone is parameterized as length and angle
	// in this case the cone is parametrized as length and arclength
	meanRadius = (m_cone.RadiusAtLength(m_extBbox.Min()[0])
		+ m_cone.RadiusAtLength(m_extBbox.Max()[0])) / 2;
	length = m_extBbox.Max()[0] - m_extBbox.Min()[0];
	meanLength = (m_extBbox.Max()[0] + m_extBbox.Min()[0]) / 2;
	// the radial extent
	radialExtent = m_extBbox.Max()[1] - m_extBbox.Min()[1];
	// We suggest a cylinder if the opening angle of the cone is so small
	// that over the whole height the difference is less than distThresh
	if(std::sin(m_cone.Angle()) * length / 2 < distThresh)
	{
		// construct the cylinder
		// it has the same axis as the cone
		// and we use the average radius of the cone
		Cylinder cylinder(m_cone.AxisDirection(), m_cone.Center(), 
			meanRadius);
		suggestions->push_back(new CylinderPrimitiveShape(cylinder));
		suggestions->back()->Release();
	}

	// We suggest a sphere if a curvature of mean radius along the height
	// does not introduce too large an error
	float sphereRadius = std::tan(m_cone.Angle()) * meanLength;
	float radiusDiff = (std::sqrt(sphereRadius * sphereRadius + length * length / 4)
		- sphereRadius) / 2;
	if(radiusDiff < distThresh)
	{
		// the center of the sphere is given as the point on the axis
		// with the height of the mean length
		Vec3f center = (meanLength / std::cos(m_cone.Angle()))
			* m_cone.AxisDirection() + m_cone.Center();
		Sphere sphere(center, sphereRadius + radiusDiff);
		suggestions->push_back(new SpherePrimitiveShape(sphere));
		suggestions->back()->Release();
	}

	// We suggest a plane if the mean radius causes only a small error
	// for this we need the angular extent in the curved direction of the cone
	radiusDiff = meanRadius - std::sin(radialExtent) * meanRadius;
	if(radiusDiff < distThresh)
	{
		GfxTL::Vector2Df bboxCenter;
		m_extBbox.Center(&bboxCenter);
		Vec3f pos, normal;
		InSpace(bboxCenter[0], bboxCenter[1] * m_cone.RadiusAtLength(bboxCenter[0]),
			&pos, &normal);
		Plane plane(pos, normal);
		suggestions->push_back(new PlanePrimitiveShape(plane));
		suggestions->back()->Release();
	}*/
}