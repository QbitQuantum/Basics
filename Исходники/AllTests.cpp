void testVector3Reflect()
{
	Vector3 vec = Vector3(0.0f, -0.5f, -0.5f).normal();
	Vector3 norm(0.0f, 1.0f, 0.0f);

	Vector3 result = vec.reflect(norm);
	assert(result == Vector3(0.0f, 0.5f, -0.5f).normal());

	vec = Vector3(-0.009f, -0.066f, 0.998f).normal();
	norm = Vector3(-0.130f, -0.985f, -0.109f).normal();

	result = vec.reflect(norm).normal();
}