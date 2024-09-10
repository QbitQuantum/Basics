void PySTGMEDIUM::Close()
{
	if (medium.tymed) {
		ReleaseStgMedium(&medium);
		memset(&medium, 0, sizeof(medium));
		assert(!medium.tymed);
	}
}