// ---------------------------------------------------------------
// GetBitmapFile
//
// Returns a BBitmap object for the bitmap file named kName.
// The user has to delete this object.
//
// Preconditions:
//
// Parameters: kName, the name of the bitmap file
//             roster, BTranslatorRoster used to do the translation
//
// Postconditions:
//
// Returns: NULL, if the file couldn't be opened or couldn't
//                be translated to a BBitmap
//          BBitmap * to the bitmap file named kName
// ---------------------------------------------------------------
BBitmap *
BTranslationUtils::GetBitmapFile(const char *kName, BTranslatorRoster *roster)
{
	if (!be_app || !kName || kName[0] == '\0')
		return NULL;
		
	BPath path;
	if (kName[0] != '/') {
		// If kName is a relative path, use the path of the application's
		// executable as the base for the relative path
		app_info info;
		if (be_app->GetAppInfo(&info) != B_OK)
			return NULL;
		BEntry appRef(&info.ref);
		if (path.SetTo(&appRef) != B_OK)
			return NULL;
		if (path.GetParent(&path) != B_OK)
			return NULL;
		if (path.Append(kName) != B_OK)
			return NULL;

	} else if (path.SetTo(kName) != B_OK)
		return NULL;
		
	BFile bitmapFile(path.Path(), B_READ_ONLY);
	if (bitmapFile.InitCheck() != B_OK)
		return NULL;

	return GetBitmap(&bitmapFile, roster);
		// Translate the data in memio using the BTranslatorRoster roster
}