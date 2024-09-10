void CStatsOverlayWindow::Update(unsigned int frames)
{
	auto windowRect = GetWindowRect();

	auto screenDc = Framework::Win32::CClientDeviceContext(NULL);
	auto memDc = Framework::Win32::CMemoryDeviceContext(screenDc);
	auto memBitmap = Framework::Win32::CBitmap(CreateCompatibleBitmap(screenDc, windowRect.Width(), windowRect.Height()));
	memDc.SelectObject(memBitmap);
	memDc.SelectObject(m_font);
	SetTextColor(memDc, RGB(0xFF, 0xFF, 0xFF));
	SetBkColor(memDc, RGB(0, 0, 0));

	{
		std::lock_guard<std::mutex> profileZonesLock(m_profilerZonesMutex);

		uint64 totalTime = 0;

		for(const auto& zonePair : m_profilerZones)
		{
			const auto& zoneInfo = zonePair.second;
			totalTime += zoneInfo.currentValue;
		}

		static const uint64 timeScale = 1000000;

		//float avgFrameTime = (static_cast<double>(totalTime) /  static_cast<double>(m_frames * timeScale));
		//profilerTextResult = string_format(_T("Avg Frame Time: %0.2fms"), avgFrameTime);

		int x = m_renderMetrics.marginX;
		int y = m_renderMetrics.marginY;
		for(const auto& zonePair : m_profilerZones)
		{
			const auto& zoneInfo = zonePair.second;
			float avgRatioSpent = (totalTime != 0) ? static_cast<double>(zoneInfo.currentValue) / static_cast<double>(totalTime) : 0;
			float avgMsSpent = (frames != 0) ? static_cast<double>(zoneInfo.currentValue) / static_cast<double>(frames * timeScale) : 0;
			float minMsSpent = (zoneInfo.minValue != ~0ULL) ? static_cast<double>(zoneInfo.minValue) / static_cast<double>(timeScale) : 0;
			float maxMsSpent = static_cast<double>(zoneInfo.maxValue) / static_cast<double>(timeScale);
			memDc.TextOut(x + 0  , y, string_cast<std::tstring>(zonePair.first).c_str());
			memDc.TextOut(x + (m_renderMetrics.fontSizeX * 10), y, string_format(_T("%6.2f%%"), avgRatioSpent * 100.f).c_str());
			memDc.TextOut(x + (m_renderMetrics.fontSizeX * 20), y, string_format(_T("%6.2fms"), avgMsSpent).c_str());
			memDc.TextOut(x + (m_renderMetrics.fontSizeX * 30), y, string_format(_T("%6.2fms"), minMsSpent).c_str());
			memDc.TextOut(x + (m_renderMetrics.fontSizeX * 40), y, string_format(_T("%6.2fms"), maxMsSpent).c_str());
			y += m_renderMetrics.fontSizeY + m_renderMetrics.spaceY;
		}

		{
			float totalAvgMsSpent = (frames != 0) ? static_cast<double>(totalTime) / static_cast<double>(frames * timeScale) : 0;
			memDc.TextOut(x + (m_renderMetrics.fontSizeX * 20), y, string_format(_T("%6.2fms"), totalAvgMsSpent).c_str());
			y += m_renderMetrics.fontSizeY + m_renderMetrics.spaceY;
		}

		for(auto& zonePair : m_profilerZones) { zonePair.second.currentValue = 0; }
	}

	POINT dstPt = { windowRect.Left(), windowRect.Top() };
	SIZE dstSize = { windowRect.Width(), windowRect.Height() };
	POINT srcPt = { 0, 0 };

	BOOL result = UpdateLayeredWindow(m_hWnd, screenDc, &dstPt, &dstSize, memDc, &srcPt, RGB(0, 0, 0), nullptr, ULW_COLORKEY);
	assert(result == TRUE);
}