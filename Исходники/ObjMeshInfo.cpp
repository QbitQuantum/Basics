void getFolder(WCHAR * folder, WCHAR * wfile)
{
	// now we need to get the containing folder of the obj file
	// this only works if the mtl and jpg files are in the same folder
	// but it shouldn't matter where that folder is

	std::vector <WCHAR *> result;

	WCHAR * res = wcstok(wfile, L"\\");
	while (res)
	{
		result.push_back(res);
		res = wcstok(NULL, L"\\");
	}

	// the last element of the result vector should be the filename, and everything else can be concatenated to make the containing folder

	USHORT resSize = result.size();

	// make the folder string empty
	wcscpy(folder, L"");

	WCHAR *slash = L"\\";

	for (int i = 0; i < resSize - 1; i++) // -1 to exclude last element
	{
		wcscat(folder, result[i]);
		wcscat(folder, slash);
	}
}