static void DrawTimeSlice(std::deque<TimeSlice>& frames, const spring_time curTime, const spring_time maxHist, const float drawArea[4])
{
	// remove old entries
	while (!frames.empty() && (curTime - frames.front().second) > maxHist) {
		frames.pop_front();
	}

	const float y1 = drawArea[1];
	const float y2 = drawArea[3];

	// render
	CVertexArray* va = GetVertexArray();
	va->Initialize();
	for (TimeSlice& ts: frames) {
		float x1 = (ts.first % maxHist).toSecsf() / maxHist.toSecsf();
		float x2 = (ts.second % maxHist).toSecsf() / maxHist.toSecsf();
		x2 = std::max(x1 + globalRendering->pixelX, x2);

		x1 = drawArea[0] + x1 * (drawArea[2] - drawArea[0]);
		x2 = drawArea[0] + x2 * (drawArea[2] - drawArea[0]);

		va->AddVertex0(x1, y1, 0.0f);
		va->AddVertex0(x1, y2, 0.0f);
		va->AddVertex0(x2, y2, 0.0f);
		va->AddVertex0(x2, y1, 0.0f);

		const float mx1 = x1 + 3 * globalRendering->pixelX;
		const float mx2 = x2 - 3 * globalRendering->pixelX;
		if (mx1 < mx2) {
			va->AddVertex0(mx1, y1 + 3 * globalRendering->pixelX, 0.0f);
			va->AddVertex0(mx1, y2 - 3 * globalRendering->pixelX, 0.0f);
			va->AddVertex0(mx2, y2 - 3 * globalRendering->pixelX, 0.0f);
			va->AddVertex0(mx2, y1 + 3 * globalRendering->pixelX, 0.0f);
		}
	}

	va->DrawArray0(GL_QUADS);
}