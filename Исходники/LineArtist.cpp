void LineArtist::drawLine(f32 x1, f32 y1, f32 x2, f32 y2, const Color& color)
{
	sf::Vertex vtxList[4];

	VectorF begin = { x1, y1 };
	VectorF end = { x2, y2 };

	VectorF direction = end - begin;
	direction.normalize();

	VectorF perpendicularVec = { -direction.y, direction.x };

	VectorF offset = (m_thickness / 2.0f) * perpendicularVec;

	VectorF tempVtxList[4] = {
		{ begin + offset },
		{ end + offset },
		{ end - offset },
		{ begin - offset }
	};

	const sf::Color sfColor = sf::Color(color.getRgba());

	for (i32 i = 0; i < 4; ++i)
	{
		vtxList[i].position = {
			tempVtxList[i].x, tempVtxList[i].y
		};
		vtxList[i].color = sfColor;
	}

	m_sharedWin.getObject()->draw(vtxList, 4, sf::Quads, m_renderStates);
}