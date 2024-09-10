Vector3F AccInterior::computeNormal() const
{
	Vector3F res = _cornerNormals[0] * _valence;
	res += _cornerNormals[1] * 2.f;
	res += _cornerNormals[3] * 2.f;
	res += _cornerNormals[2];
	return res / (_valence + 5.f);
	res.normalize();
	return res;
}