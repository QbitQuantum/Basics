inline void serialize(JsonBox::Value & o, const sf::Transform & t)
{
	const float * v = t.getMatrix();

	JsonBox::Array a;
	a.resize(16);

	for(u32 i = 0; i < 16; ++i)
	{
		a[i] = v[i];
	}

	o = a;
}