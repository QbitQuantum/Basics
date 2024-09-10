bool DielectricMaterial::Scatter( const Ray& ray, const HitRecord& record, Vector3& attenuation, Ray& scattered ) const
{
	attenuation = Vector3( 1.f, 1.f, 1.f );
	const float dirDotNormal = ray.Direction().Dot( record.normal );

	Vector3 outwardNormal;
	float niOverNt;
	float cosine;
	
	if ( dirDotNormal > 0.f )
	{
		outwardNormal = -record.normal;
		niOverNt = refractionIndex;
		//cosine = refractionIndex * dirDotNormal / ray.Direction().Length();
		cosine = dirDotNormal / ray.Direction().Length();
		cosine = std::sqrt( 1.f - refractionIndex * refractionIndex * ( 1.f - cosine * cosine ) );
	}
	else
	{
		outwardNormal = record.normal;
		niOverNt = 1.f / refractionIndex;
		cosine = -dirDotNormal / ray.Direction().Length();
	}

	const Vector3 reflected = Reflect( ray.Direction(), record.normal );

	float reflectProbability;
	Vector3 refracted;
	if ( Refract( ray.Direction(), outwardNormal, niOverNt, refracted ) )
	{
		reflectProbability = Schlick( cosine, refractionIndex );
	}
	else
	{
		reflectProbability = 1.f;
	}

	if ( Rand01() < reflectProbability )
	{
		scattered = Ray( record.point, reflected );
	}
	else
	{
		scattered = Ray( record.point, refracted );
	}

	return true;
}