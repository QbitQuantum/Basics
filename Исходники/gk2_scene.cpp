void Scene::inverse_kinematics(vector3 pos, vector3 normal, float &a1, float &a2, float &a3, float &a4, float &a5)
{
	float l1 = .91f, l2 = .81f, l3 = .33f, dy = .27f, dz = .26f;
	normal.normalize();
	vector3 pos1 = pos + normal * l3;
	float e = sqrtf(pos1.z*pos1.z + pos1.x*pos1.x - dz*dz);
	a1 = atan2(pos1.z, -pos1.x) + atan2(dz, e);
	vector3 pos2(e, pos1.y - dy, .0f);
	a3 = -acosf(min(1.0f, (pos2.x*pos2.x + pos2.y*pos2.y - l1*l1 - l2*l2)
		/ (2.0f*l1*l2)));
	float k = l1 + l2 * cosf(a3), l = l2 * sinf(a3);
	a2 = -atan2(pos2.y, sqrtf(pos2.x*pos2.x + pos2.z*pos2.z)) - atan2(l, k);
	vector3 normal1;
	normal1 = vector3(RotateRadMatrix44('y', -a1) *
		vector4(normal.x, normal.y, normal.z, .0f));
	normal1 = vector3(RotateRadMatrix44('z', -(a2 + a3)) *
		vector4(normal1.x, normal1.y, normal1.z, .0f));
	a5 = acosf(normal1.x);
	a4 = atan2(normal1.z, normal1.y);
}