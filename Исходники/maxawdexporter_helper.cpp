void MaxAWDExporter::CopyViewer(bool network)
{
    char awdDrive[4];
    char awdPath[1024];
    char awdName[256];
    char dleFullPath[1024];
    char dleDrive[4];
    char dlePath[1024];
    char tplHtmlPath[1024];
    char tplSwfPath[1024];
    char tplJsPath[1024];
    char outHtmlPath[1024];
    char outSwfPath[1024];
    char outJsPath[1024];

    // Get paths of plug-in DLE file and output AWD file and split into
    // components to be used to concatenate input and output paths.
    //TCHAR * dleFullPath_tchar=A2W(_T(""));
    TCHAR dleFullPath_tchar[1024];
    GetModuleFileName(hInstance, dleFullPath_tchar, 1024);
    char * dleFullPath_ptr=W2A(dleFullPath_tchar);
    _splitpath_s(dleFullPath_ptr, dleDrive, 4, dlePath, 1024, NULL, 0, NULL, 0);
    _splitpath_s(awdFullPath, awdDrive, 4, awdPath, 1024, awdName, 256, NULL, 0);
    // Select which viewer SWF file to copy depending on which sandbox
    // it should be compiled for (network or local.)
    char *viewerName = network?"AwayExtensions3dsMax\\AWDHTMLViewer\\viewer_n" : "AwayExtensions3dsMax\\AWDHTMLViewer\\viewer_l";

    // Assemble paths for inputs (templates)
    _makepath_s(tplHtmlPath, 1024, dleDrive, dlePath, "AwayExtensions3dsMax\\AWDHTMLViewer\\template", "html");
    _makepath_s(tplSwfPath, 1024, dleDrive, dlePath, viewerName, "swf");
    _makepath_s(tplJsPath, 1024, dleDrive, dlePath, "AwayExtensions3dsMax\\AWDHTMLViewer\\swfobject", "js");

    // Assemble paths for outputs
    _makepath_s(outHtmlPath, 1024, awdDrive, awdPath, awdName, "html");
    _makepath_s(outSwfPath, 1024, awdDrive, awdPath, "viewer", "swf");
    _makepath_s(outJsPath, 1024, awdDrive, awdPath, "swfobject", "js");

    // Copy HTML, and evaluate any variables in the template
    CopyViewerHTML(tplHtmlPath, outHtmlPath, awdName);

    // Copy SWF and JS files as-is
    TCHAR * tplSwfPath_tchar=A2W(tplSwfPath);
    TCHAR * outSwfPath_tchar=A2W(outSwfPath);
    TCHAR * tplJsPath_tchar=A2W(tplJsPath);
    TCHAR * outJsPath_tchar=A2W(outJsPath);
    CopyFile(tplSwfPath_tchar, outSwfPath_tchar, false);
    CopyFile(tplJsPath_tchar, outJsPath_tchar, true);

    TCHAR * outHtmlPath_tchar=A2W(outHtmlPath);
    ShellExecute(NULL, _T("open"), outHtmlPath_tchar, NULL, NULL, SW_SHOWNORMAL);
    free (tplSwfPath_tchar);
    free (outSwfPath_tchar);
    free (tplJsPath_tchar);
    free (outJsPath_tchar);
    free (dleFullPath_ptr);
    free (outHtmlPath_tchar);
}