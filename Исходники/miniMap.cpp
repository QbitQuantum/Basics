void CMiniMap::DrawNotes()
{
	if (notes.empty()) {
		return;
	}

	const float baseSize = gs->mapx * SQUARE_SIZE;
	CVertexArray* va = GetVertexArray();
	va->Initialize();
	std::list<Notification>::iterator ni = notes.begin();
	while (ni != notes.end()) {
		const float age = gu->gameTime - ni->creationTime;
		if (age > 2) {
			ni = notes.erase(ni);
			continue;
		}
		for (int a = 0; a < 3; ++a) {
			const float modage = age + a * 0.1f;
			const float rot = modage * 3;
			float size = baseSize - modage * baseSize * 0.9f;
			if (size < 0){
				if (size < -baseSize * 0.4f) {
					continue;
				} else if (size > -baseSize * 0.2f) {
					size = modage * baseSize * 0.9f - baseSize;
				} else {
					size = baseSize * 1.4f - modage * baseSize * 0.9f;
				}
			}
			const float sinSize = fastmath::sin(rot) * size;
			const float cosSize = fastmath::cos(rot) * size;

			const unsigned char color[4]    = {
			      (unsigned char)(ni->color[0] * 255),
			      (unsigned char)(ni->color[1] * 255),
			      (unsigned char)(ni->color[2] * 255),
			      (unsigned char)(ni->color[3] * 255)
			};
			va->AddVertexC(float3(ni->pos.x + sinSize, ni->pos.z + cosSize, 0.0f),color);
			va->AddVertexC(float3(ni->pos.x + cosSize, ni->pos.z - sinSize, 0.0f),color);
			va->AddVertexC(float3(ni->pos.x + cosSize, ni->pos.z - sinSize, 0.0f),color);
			va->AddVertexC(float3(ni->pos.x - sinSize, ni->pos.z - cosSize, 0.0f),color);
			va->AddVertexC(float3(ni->pos.x - sinSize, ni->pos.z - cosSize, 0.0f),color);
			va->AddVertexC(float3(ni->pos.x - cosSize, ni->pos.z + sinSize, 0.0f),color);
			va->AddVertexC(float3(ni->pos.x - cosSize, ni->pos.z + sinSize, 0.0f),color);
			va->AddVertexC(float3(ni->pos.x + sinSize, ni->pos.z + cosSize, 0.0f),color);
		}
		++ni;
	}
	va->DrawArrayC(GL_LINES);
}