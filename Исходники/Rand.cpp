	float Rand(float _min, float _max)
	{
		return _min + Rand() * (_max - _min);
	}