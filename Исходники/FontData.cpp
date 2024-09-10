	RectF FontData::draw(const String& codePoints, const Vec2& pos, const ColorF& color, double lineSpacingScale)
	{
		if (!render(codePoints))
		{
			return RectF(pos, 0);
		}
		
		Vec2 penPos(pos);
		double maxPosX = DBL_MIN;
		int32 lineCount = 0;
		
		for (const auto codePoint : codePoints)
		{
			if (codePoint == U'\n')
			{
				penPos.x = pos.x;
				penPos.y += m_lineSpacing * lineSpacingScale;
				++lineCount;
				continue;
			}
			else if (codePoint == U'\t')
			{
				maxPosX = std::max(maxPosX, penPos.x + m_tabWidth);
				penPos.x += m_tabWidth;
				continue;
			}
			else if (!IsControl(codePoint))
			{
				if (lineCount == 0)
				{
					++lineCount;
				}

				const auto& glyphInfo = m_glyphs[m_glyphIndexTable[codePoint]];
				const RectF region = m_texture(glyphInfo.bitmapRect).draw(penPos + glyphInfo.offset, color);
				const int32 characterWidth = glyphInfo.xAdvance;
				maxPosX = std::max(maxPosX, region.x + characterWidth);
				penPos.x += glyphInfo.xAdvance;
			}
		}

		if (!lineCount)
		{
			return RectF(pos, 0);
		}
		
		return RectF(pos, maxPosX - pos.x, lineCount * m_lineSpacing * lineSpacingScale);
	}