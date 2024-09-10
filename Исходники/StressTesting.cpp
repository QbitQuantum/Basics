bool StressTest::OpenFile(const WCHAR *fileName)
{
    wprintf(L"%s\n", fileName);
    fflush(stdout);

    LoadArgs args(fileName);
    args.forceReuse = rand() % 3 != 1;
    WindowInfo *w = LoadDocument(args);
    if (!w)
        return false;

    if (w == win) { // WindowInfo reused
        if (!win->IsDocLoaded())
            return false;
    } else if (!w->IsDocLoaded()) { // new WindowInfo
        CloseWindow(w, false);
        return false;
    }

    // transfer ownership of stressTest object to a new window and close the
    // current one
    assert(this == win->stressTest);
    if (w != win) {
        if (win->IsDocLoaded()) {
            // try to provoke a crash in RenderCache cleanup code
            ClientRect rect(win->hwndFrame);
            rect.Inflate(rand() % 10, rand() % 10);
            SendMessage(win->hwndFrame, WM_SIZE, 0, MAKELONG(rect.dx, rect.dy));
            if (win->AsFixed())
                win->cbHandler->RequestRendering(1);
            win->RepaintAsync();
        }

        WindowInfo *toClose = win;
        w->stressTest = win->stressTest;
        win->stressTest = nullptr;
        win = w;
        CloseWindow(toClose, false);
    }
    if (!win->IsDocLoaded())
        return false;

    win->ctrl->SetDisplayMode(DM_CONTINUOUS);
    win->ctrl->SetZoomVirtual(ZOOM_FIT_PAGE);
    win->ctrl->GoToFirstPage();
    if (win->tocVisible || gGlobalPrefs->showFavorites)
        SetSidebarVisibility(win, win->tocVisible, gGlobalPrefs->showFavorites);

    currPage = pageRanges.At(0).start;
    win->ctrl->GoToPage(currPage, false);
    currPageRenderTime.Start();
    ++filesCount;

    pageForSearchStart = (rand() % win->ctrl->PageCount()) + 1;
    // search immediately in single page documents
    if (1 == pageForSearchStart) {
        // use text that is unlikely to be found, so that we search all pages
        win::SetText(win->hwndFindBox, L"!z_yt");
        FindTextOnThread(win, FIND_FORWARD, true);
    }

    int secs = SecsSinceSystemTime(stressStartTime);
    ScopedMem<WCHAR> tm(FormatTime(secs));
    ScopedMem<WCHAR> s(str::Format(L"File %d: %s, time: %s", filesCount, fileName, tm));
    win->ShowNotification(s, NOS_PERSIST, NG_STRESS_TEST_SUMMARY);

    return true;
}