//get font definitions from a line of xml, insert glyph information into the map
void DistanceFieldFont::ParseChar(const StringRange &r)
{
	std::stringstream ss(r.ToString());
	std::string token;

	Uint32 id = 0;
	double x = 0.0;
	double y = 0.0;
	double uSize = 0.0;
	double vSize = 0.0;
	double xoffset = 0.0;
	double yoffset = 0.0;
	double advance = 0.0;

	while (ss >> token) {
			std::pair<std::string, std::string> pair;
			split_token(token, pair);

			//only care about some values
			if (pair.first == "id")
				id = get_value<Uint32>(pair.second);
			else if (pair.first == "x")
				x = get_value<double>(pair.second);
			else if (pair.first == "y")
				y = get_value<double>(pair.second);
			else if (pair.first == "width")
				uSize = get_value<double>(pair.second);
			else if (pair.first == "height")
				vSize = get_value<double>(pair.second);
			else if (pair.first == "xoffset")
				xoffset = get_value<float>(pair.second);
			else if (pair.first == "yoffset")
				yoffset = get_value<float>(pair.second);
			else if (pair.first == "xadvance")
				advance = get_value<float>(pair.second);
	}

	const float scale = 1.f/m_fontSize;
	Glyph g;
	g.uv = vector2f(float(x)/m_sheetSize.x, float(y)/m_sheetSize.y);
	g.uvSize = vector2f(float(uSize)/m_sheetSize.x, float(vSize)/m_sheetSize.y);
	g.size = vector2f(float(uSize), float(vSize)) * scale;
	g.offset = vector2f(float(xoffset), float(m_lineHeight-vSize-yoffset)) * scale;
	g.xAdvance = advance * scale;
	m_glyphs[id] = g;
}