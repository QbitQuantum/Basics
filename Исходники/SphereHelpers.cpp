	float SphereHelpers::calcAngleBetweenTwoVectorsRad(Vector3f a, Vector3f b)
	{
		float length_a = sqrt(a.dot(a));
		float length_b = sqrt(b.dot(b));

		float denominator = length_a * length_b;
		float numerator = a.dot(b);

		return acos(numerator / denominator);
	}