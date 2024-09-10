/****************************************************************************
PARAMETERS:
URL - New URL for the page to load

RETURNS:
True if page loaded successfully, false if not

REMARKS:
Remove an applet from the manager. Called during applet destruction
****************************************************************************/
bool wxHtmlAppletWindow::LoadPage(
    const wxString& link)
{
    wxString href(link);

    if (link.GetChar(0) == '?'){
        wxString cmd = link.BeforeFirst('=');
        wxString cmdValue = link.AfterFirst('=');

        // Launches the default Internet browser for the system.
        if(!(cmd.CmpNoCase("?EXTERNAL"))) {
            return wxSpawnBrowser(this, cmdValue.c_str());
            }

        // Launches an external program on the system.
        if (!(cmd.CmpNoCase("?EXECUTE"))) {
            int waitflag = P_NOWAIT;
            bool ret;
            wxString currentdir;
            wxString filename, path, ext;

            // Parse the params sent to the execute command. For now the only
            // parm is "wait". wait will cause spawn wait, default is nowait.
            // Since we only need one param for now I am not going to make this
            // any smater then it needs to be. If we need more params later i'll
            // fix it.
            int i = cmdValue.Find('(');
            if (i != -1) {
                wxString param = cmdValue.AfterFirst('(');
                cmdValue.Truncate(i);
                if (!param.CmpNoCase("wait)"))
                    waitflag = P_WAIT;
                }

            currentdir = wxGetCwd();
            //we don't want to change the path of the virtual file system so we have to use these
            //functions rather than the filesystem
            wxSplitPath(cmdValue, &path, &filename, &ext);
            if (path.CmpNoCase("") != 0) wxSetWorkingDirectory(path);

            ret = !spawnl( waitflag, cmdValue , NULL );
            //HACK should use wxExecute
            //ret = wxExecute(filename, bool sync = FALSE, wxProcess *callback = NULL)
            wxSetWorkingDirectory(currentdir);

            return ret;
            }

        // Looks for a href in a variable stored as a cookie. The href can be
        // changed on the fly.
        if (!(cmd.CmpNoCase("?VIRTUAL"))){
            wxObject *obj = FindCookie(cmdValue);
            VirtualData *virtData = wxDynamicCast(obj,VirtualData);
            if (virtData) {
                // recurse and loadpage, just in case the link is like another
                // ? link
                return LoadPage(virtData->GetHref());
                }
            else {
#ifdef CHECKED
                wxLogError(_T("VIRTUAL LINK ERROR: '%s' does not exist."), cmdValue.c_str());
#endif
                return true;
                }
            }

        // This launches a qlet - It is like an applet but is more generic in that it
        // can be of any wxWin type so it then has the freedom to do more stuff.
        if (!(cmd.CmpNoCase("?WXPLUGIN"))){
            if (!cmdValue.IsNull()) {
                // TODO: We are going to need to add code to parse the command line
                //       parameters string in here in the future...
                wxString cmdLine = link.AfterFirst('(');
                cmdLine = cmdLine.BeforeLast(')');
                if (!CreatePlugIn(cmdValue,cmdLine)) {
#ifdef CHECKED
                    wxLogError(_T("Launch PlugIn ERROR: '%s' does not exist."), cmdValue.c_str());
#endif
                    }
                }
             return true;
            }

        // This used in a link or href will take you back in the history.
        if (!(cmd.CmpNoCase("?BACK"))){
            HistoryBack();
            return true;
            }

        // This used in a link or href will take you forward in the history
        if (!(cmd.CmpNoCase("?FORWARD"))){
            HistoryForward();
            return true;
            }
        }

    // Inform all the applets that the new page is being loaded
    for (wxAppletList::Node *node = m_AppletList.GetFirst(); node; node = node->GetNext())
        (node->GetData())->OnLinkClicked(wxHtmlLinkInfo(href));
    Show(false);

    m_openedlast = href;
    bool stat = wxHtmlWindow::LoadPage(href);
    Show(true);

    // Enable/Dis the navbar tools
    if (m_NavBarEnabled) {
        m_NavBar->EnableTool(m_NavForwardId,HistoryCanForward());
        m_NavBar->EnableTool(m_NavBackId,HistoryCanBack());
        }
    return stat;
}