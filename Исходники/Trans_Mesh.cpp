float Trans_Mesh::Ray_Tri_Intersect(const vec3& rayorig, const vec3& raydir, mat4& world, uint16_t startindex, uint16_t numindices) const{
	world.inverse();
	vec3 org(rayorig*world), di(raydir);// transform these to the mesh's space so the checks are in object space, not world space
	TransformNormal(di, world);
	// do all checks in OBJECT SPACE!!!
	di*=20000.0f;//make sure the ray is long enough
	return RayTriangleIntersect(org, di, &Vertices[0], &Indices[startindex],numindices);
}