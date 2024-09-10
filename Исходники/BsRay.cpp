	std::pair<bool, float> Ray::intersects(const Sphere& s) const
	{
		return s.intersects(*this);
	}