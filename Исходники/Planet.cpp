void CPlanet::RefreshObject(Object *obj)
{
	CVector pos = obj->GetPosition();

	// Get the height of the place specified by vector to compute ideal
	// position of the object
	float fHeight = m_mapHeight.GetHeight(pos, pos.Magnitude());
	pos.Normalize();
	pos *= fHeight;

	// Associate object with particular triangle on the planet, so it can change its
	// position later when the planet is updated (see onTriangleUpdated)
	CROAMTriangle *tri = getCords(pos * -1, pos);
	if (tri) {
		if (obj->tri != tri) {
			if (obj->tri) {
				std::vector<Object *>::iterator it = std::find(obj->tri->objects.begin(), obj->tri->objects.end(), obj);
				if (it != obj->tri->objects.end()) {
					obj->tri->objects.erase(it);
				}
			}
			obj->tri = tri;
			tri->objects.push_back(obj);
		}

		obj->SetPosition(pos);

		if (obj->rotateWithTriangle) {
			obj->RotateToVector(tri->GetNormal());
		}
		else {
			obj->RotateToVector(pos, true);
		}
	}
	else {
		obj->RotateToVector(pos);
		std::cerr << "WARNING: No triangle for newly added object?!\n";
	}
}