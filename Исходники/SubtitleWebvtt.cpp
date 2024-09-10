BOOL CSubtitleWebvttReader::Probe(wchar_t *text)
{
	if (bProbe) return FALSE;
	bProbe = TRUE;
	return _wcsicmp(text, L"WEBVTT") == 0;
}