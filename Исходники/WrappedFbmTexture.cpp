glm::vec3 WrappedFbmTexture::getColor(const ShadeRec& sr)const
{
	float noiseV = expansionNumber * noise->valueFBM(sr.localHitPoint);
	float value = noiseV - FLOOR(noiseV);

	return lerp(value, colorMin, colorMax);
}