void DrawDownloadsOverlay(UIContext &dc) {
	// Thin bar at the top of the screen like Chrome.
	std::vector<float> progress = g_DownloadManager.GetCurrentProgress();
	if (progress.empty()) {
		return;
	}

	static const uint32_t colors[4] = {
		0xFFFFFFFF,
		0xFFCCCCCC,
		0xFFAAAAAA,
		0xFF777777,
	};

	dc.Begin();
	int h = 5;
	for (size_t i = 0; i < progress.size(); i++) {
		float barWidth = 10 + (dc.GetBounds().w - 10) * progress[i];
		Bounds bounds(0, h * i, barWidth, h);
		UI::Drawable solid(colors[i & 3]);
		dc.FillRect(solid, bounds);
	}
	dc.End();
	dc.Flush();
}