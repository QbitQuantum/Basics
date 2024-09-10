void
getDropData(IDataObject* dataObject)
{
    // construct a FORMATETC object
    FORMATETC fmtEtc = { CF_HDROP, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
    STGMEDIUM stgMed;

    // See if the dataobject contains any DROP stored as a HGLOBAL
    if (dataObject->QueryGetData(&fmtEtc) == S_OK) {
        if (dataObject->GetData(&fmtEtc, &stgMed) == S_OK) {
            // get data here
            PVOID data = GlobalLock(stgMed.hGlobal);

            // data object global handler contains:
            // DROPFILESfilename1 filename2 two spaces as the end
            // TODO: get multiple filenames
            wchar_t* wcData = (wchar_t*)((LPBYTE)data + sizeof(DROPFILES));

            // convert wchar to char
            char* filename = new char[wcslen(wcData) + 1];
            filename[wcslen(wcData)] = '\0';
            wcstombs(filename, wcData, wcslen(wcData));

            MSWindowsDropTarget::instance().setDraggingFilename(filename);
            
            GlobalUnlock(stgMed.hGlobal);

            // release the data using the COM API
            ReleaseStgMedium(&stgMed);

            delete[] filename;
        }
    }
}