void IntelFaceScanner::renderScan()
{
  // Setup the output path to a writable location.
    size_t unused;
    WCHAR* pUserProfilePath;
    _wdupenv_s(&pUserProfilePath, &unused, L"USERPROFILE");
    const PXC3DScan::FileFormat format = PXC3DScan::PLY; // OBJ, PLY or STL
    const pxcCHAR* ext = PXC3DScan::FileFormatToString(format);
    const size_t FSIZE = 4096;
    WCHAR filename[FSIZE];
    //swprintf_s(filename, FSIZE, L"%s\\Documents\\Pierre3dscan.%s", pUserProfilePath, ext);
    swprintf_s(filename, FSIZE, L".\\data\\3dscan.%s", ext);

    // If applicable, reconstruct the 3D Mesh to the specific file/format
	pxcStatus result = PXC_STATUS_NO_ERROR;
    bool bMeshSaved = false;
    if (scanner->IsScanning())
    {
        wprintf_s(L"Generating %s...", filename);
        result = scanner->Reconstruct(format, filename);
        if (result >= PXC_STATUS_NO_ERROR)
        {
            bMeshSaved = true;
            wprintf_s(L"done.\n");
        }
		else if (result == PXC_STATUS_FILE_WRITE_FAILED)
        {
            wprintf_s(L"the file could not be created using the provided path. Aborting.\n");
        }
        else if (result == PXC_STATUS_ITEM_UNAVAILABLE || result == PXC_STATUS_DATA_UNAVAILABLE)
        {
            wprintf_s(L"no scan data found. Aborting.\n");
        }
        else if (result < PXC_STATUS_NO_ERROR)
        {
            wprintf_s(L"\nError: Reconstruct returned %d\n", result);
        }
    }
    else wprintf_s(L"Empty scanning volume.\n");
}