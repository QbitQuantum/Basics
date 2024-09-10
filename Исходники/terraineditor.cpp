// 지형에 텍스쳐를 입힌다.
void cTerrainEditor::BrushTexture( const cTerrainCursor &cursor )
{
	RET(!cursor.GetBrushTexture());

	if (GetTopLayer().texture != cursor.GetBrushTexture())
	{
		// 빈 레이어 일 때만 새 레이어를 추가한다.
		if (GetTopLayer().texture && !AddLayer())
			return; // 더 이상 추가할 레이어가 없다면 종료한다.
	}

	sSplatLayer &curLayer = GetTopLayer();
	const int layerIdx = m_layer.size()-1;
	curLayer.texture = (cTexture*)cursor.GetBrushTexture();
	//const int MASK = ~(0xFF << (24 - (layerIdx * 8)));
	const int MASK = ~GetAlphaMask(layerIdx);

	float u, v;
	GetTextureUV(cursor.GetCursorPos(), u, v);

	const float WIDTH = GetTerrainWidth();
	const float HEIGHT = GetTerrainHeight();
	
	D3DLOCKED_RECT lockrect;
	m_alphaTexture.Lock(lockrect);

	BYTE *pbits = (BYTE*)lockrect.pBits;
	for (int ay=0; ay < ALPHA_TEXTURE_SIZE_H; ++ay)
	{
		for (int ax=0; ax < ALPHA_TEXTURE_SIZE_W; ++ax)
		{
			const float au = (float)ax / (float)(ALPHA_TEXTURE_SIZE_W - 1);
			const float av = (float)ay / (float)(ALPHA_TEXTURE_SIZE_H - 1);

			const float ru = fabs(au-u) * WIDTH;
			const float rv = fabs(av-v) * HEIGHT;
			const float len = sqrt( ru*ru + rv*rv );

			// A8R8G8B8 Format
			DWORD *ppixel = (DWORD*)(pbits + (ax*4) + (lockrect.Pitch * ay));

			if (len <= cursor.GetInnerBrushRadius())
			{
				int color = (int)(255.f * cursor.GetInnerBrushAlpha());
				if (cursor.IsEraseMode()) // 지우개 모드일 때는 역의 값을 넣게한다.
					color = 255-color;
				color = color << (24 - (layerIdx * 8));

				*ppixel = color | (*ppixel & MASK);
			}
			else if (len <= cursor.GetOuterBrushRadius())
			{
				// 보간
				const float w = (float)cursor.GetOuterBrushRadius() - (float)cursor.GetInnerBrushRadius();
				const float delta = 1.f - ((len - cursor.GetInnerBrushRadius()) / w);
				int color = (int)(cursor.GetInnerBrushAlpha() * delta * 255.f);
				if (cursor.IsEraseMode()) // 지우개 모드일 때는 역의 값을 넣게한다.
					color = 255-color;

				const int dest = (*ppixel >> (24 - (layerIdx * 8))) & 0xFF;

				if ( (cursor.IsEraseMode() && (color < dest)) ||
					(!cursor.IsEraseMode() && (color > dest)))
				{
					color = color << (24 - (layerIdx * 8));
					*ppixel = color | (*ppixel & MASK);
				}
			}
		}
	}

	m_alphaTexture.Unlock();
}