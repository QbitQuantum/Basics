exifoff_t ExifInternetIO::size()
{
	unsigned int sz;
	InternetQueryDataAvailable(mHInternet, &sz, 0, 0);
	return sz;
}