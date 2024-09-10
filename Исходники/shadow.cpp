void Shadow::calculateFrustumVertices(const Light &light, const Actor &actor, float lx, float ly, vec3 &ntl, vec3 &ntr, vec3 &nbl, vec3 &nbr, vec3 &ftl, vec3 &ftr, vec3 &fbl, vec3 &fbr)
{
	const vec3 &lightPosition = light.getPosition();
	const vec3 &lightCenter = actor.getPos();
	const vec3 lightUp(0.0f, 1.0f, 0.0f);

	float tanX = tanf(lx);
	float tanY = tanf(ly);
	float nh = nearClip * tanY;
	float nw = nearClip * tanX;
	float fh = farClip  * tanY;
	float fw = farClip  * tanX;

	vec3 dir,nc,fc,X,Y,Z;

	Z = lightPosition - lightCenter;
	Z.normalize();

	X = lightUp.cross(Z);
	X.normalize();

	Y = Z.cross(X);

	nc = lightPosition - Z * nearClip;
	fc = lightPosition - Z * farClip;

	ntl = nc + Y * nh - X * nw;
	ntr = nc + Y * nh + X * nw;
	nbl = nc - Y * nh - X * nw;
	nbr = nc - Y * nh + X * nw;

	ftl = fc + Y * fh - X * fw;
	ftr = fc + Y * fh + X * fw;
	fbl = fc - Y * fh - X * fw;
	fbr = fc - Y * fh + X * fw;
}