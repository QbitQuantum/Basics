static BOOL IsRectOnSingleMonitor(const CRect& rect)
{
	const HMONITOR monitor = MonitorFromPoint(rect.TopLeft(), MONITOR_DEFAULTTONULL);	// Find monitor from top left of rect
	MONITORINFO info;
	info.cbSize = sizeof(info);

	if (!monitor || !GetMonitorInfo(monitor, &info))		// Get monitor's info
		return false;										// fail if not on monitor or no info

	CRect intersection;
	intersection.IntersectRect(&info.rcMonitor, &rect);		// Calculate intersection between rect and monitor
	return intersection == rect;							// rect is fully on monitor iff intersection of rect and monitor is rect
}