int  DataFileSaveAsCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
    char path[300], path1[300], path2[300], name[300];
    int i, filestatus;  char *date, mon[10], day[10], yr[10];
	
    if (event == EVENT_COMMIT) {
        Fmt (name, "%s<%s.%i", dataFile.name, dataFile.ext);
        filestatus = FileSelectPopup (dataFile.dir, name, "",
                                      "Save As [file extension must be a #!]:",
                                      VAL_OK_BUTTON, 0, 0, 1, 1, path);
        switch (filestatus) {
            case VAL_EXISTING_FILE_SELECTED:
                MessagePopup ("Save As Message", "Cannot select duplicate file paths");
                break;
            case VAL_NEW_FILE_SELECTED:
                Fmt (path1, path);
                while (Scan(path1, "%s>%s[xdt92]%s", path2) == 2)
                    Fmt (path1, path2);
                Scan (path2, "%s>%s[t46]", dataFile.name);
                i = Scan (path2, "%s>%s[xdt46]%i[b2]", &dataFile.ext);
                if (i != 2)
                    MessagePopup ("File name error",
                              "File extension must be a number..."
                              "extension ignored");
                Fmt (path1, path);
                i = FindPattern (path1, 0, StringLength (path1), path2, 0, 0);
                CopyString (dataFile.dir, 0, path1, 0, i-1);  
                acquire_UpdateDataFileInfo();
                break;
        }
    }
    return 0;
}