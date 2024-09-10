char BaseMesh::triangleIntersect(const Vector3F * threeCorners, IntersectionContext * ctx) const
{
    Vector3F a = threeCorners[0];
	Vector3F b = threeCorners[1];
	Vector3F c = threeCorners[2];
	Vector3F ab = b - a;
	Vector3F ac = c - a;
	Vector3F nor = ab.cross(ac);
	nor.normalize();
	
	Ray &ray = ctx->m_ray;
	float ddotn = ray.m_dir.dot(nor);
		
	if(!ctx->twoSided && ddotn > 0.f) return 0;
	
	float t = (a.dot(nor) - ray.m_origin.dot(nor)) / ddotn;
	
	if(t < 0.f || t > ray.m_tmax) return 0;
	
	//printf("face %i %f %f", idx, t, ctx->m_minHitDistance);
	
	if(t > ctx->m_minHitDistance) return 0;
	
	Vector3F onplane = ray.m_origin + ray.m_dir * t;
	Vector3F e01 = b - a;
	Vector3F x0 = onplane - a;
	if(e01.cross(x0).dot(nor) < 0.f) return 0;
	
	//printf("pass a\n");

	Vector3F e12 = c - b;
	Vector3F x1 = onplane - b;
	if(e12.cross(x1).dot(nor) < 0.f) return 0;
	
	//printf("pass b\n");
	
	Vector3F e20 = a - c;
	Vector3F x2 = onplane - c;
	if(e20.cross(x2).dot(nor) < 0.f) return 0;
	
	//printf("pass c\n");
	
	ctx->m_hitP = onplane;
	ctx->m_hitN = nor;
	ctx->m_minHitDistance = t;
	ctx->m_geometry = (Geometry*)this;
	ctx->m_success = 1;
	return 1;
}