void CRepulseGfx::Draw()
{
	const CUnit* owner = CProjectile::owner();
	if (!owner || !repulsed) {
		return;
	}

	const float3 zdir = (repulsed->pos - owner->pos).SafeANormalize();
	const float3 xdir = (zdir.cross(UpVector)).SafeANormalize();
	const float3 ydir = xdir.cross(zdir);

	float3 xdirDS;
	float3 ydirDS;

	pos = (repulsed->pos - zdir * 10.0f) + (repulsed->speed * globalRendering->timeOffset);
	inArray = true;

	float drawsize = 10.0f;
	float alpha = std::min(255.0f, age * 10.0f);
	unsigned char col[4] = {
		(unsigned char) (color.x * alpha),
		(unsigned char) (color.y * alpha),
		(unsigned char) (color.z * alpha),
		(unsigned char) (0.2f    * alpha),
	};

	xdirDS = xdir * drawsize;
	ydirDS = ydir * drawsize;

	const AtlasedTexture* et = projectileDrawer->repulsetex;
	const float txo = et->xstart;
	const float tyo = et->ystart;
	const float txs = et->xend - et->xstart;
	const float tys = et->yend - et->ystart;

	static const int loopCountY = 4;
	static const int loopCountX = 4;

	va->EnlargeArrays(loopCountY * loopCountX * 4 + 16, 0, VA_SIZE_TC);

	for (int y = 0; y < loopCountY; ++y) { //! CAUTION: loop count must match EnlargeArrays above
		const float dy = y - 2.0f;
		const float ry = y * 0.25f;

		for (int x = 0; x < loopCountX; ++x) {
			const float dx = x - 2.00f;
			const float rx = x * 0.25f;

			va->AddVertexQTC(pos + xdirDS * (dx + 0) + ydirDS * (dy + 0) + zdir * difs[(y    ) * 5 + x    ],  txo + (ry        ) * txs, tyo + (rx        ) * tys,  col);
			va->AddVertexQTC(pos + xdirDS * (dx + 0) + ydirDS * (dy + 1) + zdir * difs[(y + 1) * 5 + x    ],  txo + (ry + 0.25f) * txs, tyo + (rx        ) * tys,  col);
			va->AddVertexQTC(pos + xdirDS * (dx + 1) + ydirDS * (dy + 1) + zdir * difs[(y + 1) * 5 + x + 1],  txo + (ry + 0.25f) * txs, tyo + (rx + 0.25f) * tys,  col);
			va->AddVertexQTC(pos + xdirDS * (dx + 1) + ydirDS * (dy + 0) + zdir * difs[(y    ) * 5 + x + 1],  txo + (ry        ) * txs, tyo + (rx + 0.25f) * tys,  col);
		}
	}

	drawsize = 7.0f;
	alpha = std::min(10.0f, age / 2.0f);
	col[0] = (unsigned char) (color.x * alpha);
	col[1] = (unsigned char) (color.y * alpha);
	col[2] = (unsigned char) (color.z * alpha);
	col[3] = (unsigned char) (alpha * 0.4f);

	const AtlasedTexture* ct = projectileDrawer->repulsegfxtex;
	const float tx = (ct->xend + ct->xstart) * 0.5f;
	const float ty = (ct->yend + ct->ystart) * 0.5f;

	static const unsigned char col2[4] = {0, 0, 0, 0};

	xdirDS = xdir * drawsize;
	ydirDS = ydir * drawsize;

	va->AddVertexQTC(owner->pos + (-xdir + ydir) * drawsize * 0.2f,  tx, ty, col2);
	va->AddVertexQTC(owner->pos + ( xdir + ydir) * drawsize * 0.2f,  tx, ty, col2);
	va->AddVertexQTC(       pos + xdirDS + ydirDS + zdir * difs[6],  tx, ty, col);
	va->AddVertexQTC(       pos - xdirDS + ydirDS + zdir * difs[6],  tx, ty, col);

	va->AddVertexQTC(owner->pos + (-xdir - ydir) * drawsize * 0.2f,  tx, ty, col2);
	va->AddVertexQTC(owner->pos + ( xdir - ydir) * drawsize * 0.2f,  tx, ty, col2);
	va->AddVertexQTC(       pos + xdirDS - ydirDS + zdir * difs[6],  tx, ty, col);
	va->AddVertexQTC(       pos - xdirDS - ydirDS + zdir * difs[6],  tx, ty, col);

	va->AddVertexQTC(owner->pos + (xdir - ydir) * drawsize * 0.2f,   tx, ty, col2);
	va->AddVertexQTC(owner->pos + (xdir + ydir) * drawsize * 0.2f,   tx, ty, col2);
	va->AddVertexQTC(       pos + xdirDS + ydirDS + zdir * difs[6],  tx, ty, col);
	va->AddVertexQTC(       pos + xdirDS - ydirDS + zdir * difs[6],  tx, ty, col);

	va->AddVertexQTC(owner->pos + (-xdir - ydir) * drawsize * 0.2f,  tx, ty, col2);
	va->AddVertexQTC(owner->pos + (-xdir + ydir) * drawsize * 0.2f,  tx, ty, col2);
	va->AddVertexQTC(       pos - xdirDS + ydirDS + zdir * difs[6],  tx, ty, col);
	va->AddVertexQTC(       pos - xdirDS - ydirDS + zdir * difs[6],  tx, ty, col);
}