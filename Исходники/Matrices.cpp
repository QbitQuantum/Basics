void mat4::createRotation(vec3 axis, float rad)
{
	axis.normalize();

	float cosine = cos(rad);
	float sine = sin(rad);

	elements[0] = cosine + pow(axis.x, 2)*(1-cosine);
	elements[1] = axis.x*axis.y*(1 - cosine) - axis.z*sine;
	elements[2] = axis.x*axis.z*(1 - cosine) + axis.y*sine;
	elements[4] = axis.y*axis.x*(1 - cosine) + axis.z*sine;
	elements[5] = cosine + pow(axis.y, 2)*(1 - cosine);
	elements[6] = axis.z*axis.y*(1 - cosine) - axis.x*sine;
	elements[8] = axis.x*axis.z*(1 - cosine) - axis.y*sine;
	elements[9] = axis.z*axis.y*(1 - cosine) + axis.x*sine;
	elements[10] = cosine + pow(axis.z, 2)*(1 - cosine);
	elements[15] = 1.0f;
}