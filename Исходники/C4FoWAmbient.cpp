void C4FoWAmbient::CreateFromLandscape(const C4Landscape& landscape, double resolution, double radius, double full_coverage)
{
	assert(resolution >= 1.);
	assert(radius >= 1.);
	assert(full_coverage > 0 && full_coverage <= 1.);

	// Clear old map
	Clear();

	Resolution = resolution;
	Radius = radius;
	FullCoverage = full_coverage;

	// Number of zoomed pixels
	LandscapeX = Landscape.GetWidth();
	LandscapeY = Landscape.GetHeight();
	SizeX = std::min<unsigned int>(static_cast<unsigned int>(ceil(LandscapeX / resolution)), pDraw->MaxTexSize);
	SizeY = std::min<unsigned int>(static_cast<unsigned int>(ceil(LandscapeY / resolution)), pDraw->MaxTexSize);

#ifndef USE_CONSOLE
	glGenTextures(1, &Tex);
	glBindTexture(GL_TEXTURE_2D, Tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SizeX, SizeY, 0, GL_RED, GL_FLOAT, nullptr);

	const C4TimeMilliseconds begin = C4TimeMilliseconds::Now();
	UpdateFromLandscape(landscape, C4Rect(0, 0, Landscape.GetWidth(), Landscape.GetHeight()));
	uint32_t dt = C4TimeMilliseconds::Now() - begin;
	LogF("Created %ux%u ambient map in %g secs", SizeX, SizeY, dt / 1000.);
#endif
}