int SyncTex::SourceToDoc(const WCHAR* srcfilename, UINT line, UINT col, UINT* page, Vec<RectI>& rects) {
    if (IsIndexDiscarded()) {
        if (RebuildIndex() != PDFSYNCERR_SUCCESS)
            return PDFSYNCERR_SYNCFILE_CANNOT_BE_OPENED;
    }
    AssertCrash(this->scanner);

    AutoFreeW srcfilepath;
    // convert the source file to an absolute path
    if (PathIsRelative(srcfilename))
        srcfilepath.Set(PrependDir(srcfilename));
    else
        srcfilepath.SetCopy(srcfilename);
    if (!srcfilepath)
        return PDFSYNCERR_OUTOFMEMORY;

    bool isUtf8 = true;
    char* mb_srcfilepath = str::conv::ToUtf8(srcfilepath).StealData();
TryAgainAnsi:
    if (!mb_srcfilepath)
        return PDFSYNCERR_OUTOFMEMORY;
    int ret = synctex_display_query(this->scanner, mb_srcfilepath, line, col);
    free(mb_srcfilepath);
    // recent SyncTeX versions encode in UTF-8 instead of ANSI
    if (isUtf8 && -1 == ret) {
        isUtf8 = false;
        mb_srcfilepath = str::conv::ToAnsi(srcfilepath).StealData();
        goto TryAgainAnsi;
    }

    if (-1 == ret)
        return PDFSYNCERR_UNKNOWN_SOURCEFILE;
    if (0 == ret)
        return PDFSYNCERR_NOSYNCPOINT_FOR_LINERECORD;

    synctex_node_t node;
    int firstpage = -1;
    rects.Reset();

    while ((node = synctex_next_result(this->scanner)) != nullptr) {
        if (firstpage == -1) {
            firstpage = synctex_node_page(node);
            if (firstpage <= 0 || firstpage > engine->PageCount())
                continue;
            *page = (UINT)firstpage;
        }
        if (synctex_node_page(node) != firstpage)
            continue;

        RectD rc;
        rc.x = synctex_node_box_visible_h(node);
        rc.y = synctex_node_box_visible_v(node) - synctex_node_box_visible_height(node);
        rc.dx = synctex_node_box_visible_width(node),
        rc.dy = synctex_node_box_visible_height(node) + synctex_node_box_visible_depth(node);
        rects.Push(rc.Round());
    }

    if (firstpage <= 0)
        return PDFSYNCERR_NOSYNCPOINT_FOR_LINERECORD;
    return PDFSYNCERR_SUCCESS;
}