status_t ExportContext::writeString(
	const BString&							string) {

	return writeString(string.String(), string.Length());
}