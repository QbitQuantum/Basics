AABB operator*(const mat3 & matrix, const AABB & AABB){ 

	vec2 aMin = AABB.min();
	vec2 aMax = AABB.max();

	vec2 mMin = matrix[2].xy;
	vec2 mMax = matrix[2].xy;

	float s, f;

	for (unsigned i = 0; i < 2; ++i)
		for (unsigned j = 0; j < 2; ++j) {

			s = aMin[j] * matrix[j][i];
			f = aMax[j] * matrix[j][i];

			if (s < f) std::swap(s, f);
			mMin[i] += s;
			mMax[i] += f;
		}

	return{ (mMin + mMax) / 2, (mMin - mMax) / 2 };
}