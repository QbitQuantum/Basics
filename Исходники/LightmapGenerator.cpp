bool LightMapGenerator::CastSpecularRay( Ray &vRayInOut, Vec3 &worldSpaceNormals )
{
	//calculate reflection ray	
	Vec3 Reflection = (worldSpaceNormals*2) - vRayInOut.m_Direction;
	Reflection.Normalize();
	//simple weight distribution
	int weight = rand()%100;
	//goes to 10,000
	float multiplier = 1.f - ((float)(weight*weight)/10000.f);//most of the time it will be near 1k so near (1-1) = 0

	//add fuzzy
	Reflection.x = Reflection.x*100 + multiplier*(float)(rand()%20) + multiplier*10.f;
	Reflection.y = Reflection.y*100 + multiplier*(float)(rand()%20) + multiplier*10.f;
	Reflection.z = Reflection.z*100 + multiplier*(float)(rand()%20) + multiplier*10.f;
	Reflection.Normalize();
	vRayInOut.m_Direction = Reflection;
	return true;
}