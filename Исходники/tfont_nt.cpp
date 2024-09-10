TPoint TFont::drawChar(TVectorImageP &image, wchar_t charcode, wchar_t nextCharCode) const

{

	GLYPHMETRICS gm;
	MAT2 mat2;
	mat2.eM11.fract = 0;
	mat2.eM12.fract = 0;
	mat2.eM21.fract = 0;
	mat2.eM22.fract = 0;
	mat2.eM11.value = 1;
	mat2.eM12.value = 0;
	mat2.eM21.value = 0;
	mat2.eM22.value = 1;

	vector<TThickPoint> points;

	UINT j = 0;

	DWORD charMemorySize = GetGlyphOutlineW(m_pimpl->m_hdc, charcode, GGO_NATIVE, &gm, 0, 0, &mat2);
	if (charMemorySize == GDI_ERROR) {
		assert(0);
		return TPoint();
	}

	LPVOID lpvBuffer = new char[charMemorySize];

	charMemorySize = GetGlyphOutlineW(m_pimpl->m_hdc, charcode, GGO_NATIVE, &gm, charMemorySize, lpvBuffer, &mat2);
	if (charMemorySize == GDI_ERROR) {
		assert(0);
		return TPoint();
	}

	TTPOLYGONHEADER *header = (TTPOLYGONHEADER *)lpvBuffer;

	while ((char *)header < (char *)lpvBuffer + charMemorySize) {
		points.clear();
		TThickPoint startPoint = toThickPoint(header->pfxStart);
		points.push_back(startPoint);

		if (header->dwType != TT_POLYGON_TYPE) {
			assert(0);
		}
		int memorySize = header->cb;

		TTPOLYCURVE *curve = (TTPOLYCURVE *)(header + 1);

		while ((char *)curve < (char *)header + memorySize) {
			switch (curve->wType) {
			case TT_PRIM_LINE:

				for (j = 0; j < curve->cpfx; j++) {
					TThickPoint p0 = points.back();
					TThickPoint p1 = toThickPoint(((*curve).apfx[j]));
					points.push_back((p0 + p1) * 0.5);
					points.push_back(p1);
				}

				break;

			case TT_PRIM_QSPLINE:

				for (j = 0; (int)j + 2 < curve->cpfx; j++) {
					TThickPoint p1 = toThickPoint(((*curve).apfx[j]));
					TThickPoint p2 = toThickPoint(((*curve).apfx[j + 1]));

					points.push_back(p1);
					points.push_back((p1 + p2) * 0.5);
				}
				points.push_back(toThickPoint(((*curve).apfx[j++])));
				points.push_back(toThickPoint(((*curve).apfx[j++])));

				break;
			case TT_PRIM_CSPLINE:
				assert(0);
				break;
			default:
				assert(0);
			}

			curve = (TTPOLYCURVE *)(&(curve->apfx)[j]);
		}

		TThickPoint p0 = points.back();
		if (!isAlmostZero(p0.x - startPoint.x) || !isAlmostZero(p0.y - startPoint.y)) {
			points.push_back((p0 + startPoint) * 0.5);
			points.push_back(startPoint);
		}

		TStroke *stroke = new TStroke();
		stroke->reshape(&(points[0]), points.size());
		stroke->setSelfLoop(true);
		image->addStroke(stroke);

		header = (TTPOLYGONHEADER *)curve;
	}

	delete[] lpvBuffer;

	image->group(0, image->getStrokeCount());

	return getDistance(charcode, nextCharCode);
}