void C4Application::ApplyResolutionConstraints()
{
	// Not changing the resolution always works anyway
	if (Config.Graphics.ResX == -1 && Config.Graphics.ResY == -1)
		return;
	// Enumerate display modes
	int32_t idx = -1, iXRes, iYRes, iBitDepth, iRefreshRate;
	int32_t best_match = -1;
	uint32_t best_delta = ~0;
	while (GetIndexedDisplayMode(++idx, &iXRes, &iYRes, &iBitDepth, &iRefreshRate, Config.Graphics.Monitor))
	{
		if (iBitDepth != Config.Graphics.BitDepth) continue;
		uint32_t delta = std::abs(Config.Graphics.ResX*Config.Graphics.ResY - iXRes*iYRes);
		if (!delta && iBitDepth == Config.Graphics.BitDepth && iRefreshRate == Config.Graphics.RefreshRate)
			return; // Exactly the expected mode
		if (delta < best_delta)
		{
			// Better match than before
			best_match = idx;
			best_delta = delta;
		}
	}
	if (best_match != -1)
	{
		// Apply next-best mode
		GetIndexedDisplayMode(best_match, &iXRes, &iYRes, &iBitDepth, &iRefreshRate, Config.Graphics.Monitor);
		if (iXRes != Config.Graphics.ResX || iYRes != Config.Graphics.ResY)
			// Don't warn if only bit depth changes
			// Also, lang table not loaded yet
			LogF("Warning: The selected resolution %dx%d is not available and has been changed to %dx%d.", Config.Graphics.ResX, Config.Graphics.ResY, iXRes, iYRes);
		Config.Graphics.ResX = iXRes; Config.Graphics.ResY = iYRes;
		Config.Graphics.BitDepth = iBitDepth;
		Config.Graphics.RefreshRate = iRefreshRate;
	}
}