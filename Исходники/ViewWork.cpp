void CViewWork::GetDocApplicationName(wxInt32 item, wxString& strBuffer) const {
    CMainDocument* pDoc = wxGetApp().GetDocument();
    RESULT*        result = wxGetApp().GetDocument()->result(item);
    RESULT*        state_result = NULL;
    wxString       strAppBuffer = wxEmptyString;
    wxString       strClassBuffer = wxEmptyString;

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    if (result) {
        state_result = pDoc->state.lookup_result(result->project_url, result->name);
        if (!state_result) {
            pDoc->ForceCacheUpdate();
            state_result = pDoc->state.lookup_result(result->project_url, result->name);
        }

        if (!state_result) return;
        WORKUNIT* wup = state_result->wup;
        if (!wup) return;
        APP* app = wup->app;
        if (!app) return;
        APP_VERSION* avp = state_result->avp;
        if (!avp) return;

        if (strlen(app->user_friendly_name)) {
            strAppBuffer = HtmlEntityDecode(wxString(state_result->app->user_friendly_name, wxConvUTF8));
        } else {
            strAppBuffer = HtmlEntityDecode(wxString(state_result->avp->app_name, wxConvUTF8));
        }
        
        if (strlen(avp->plan_class)) {
            strClassBuffer.Printf(
                wxT(" (%s)"),
                wxString(avp->plan_class, wxConvUTF8).c_str()
            );
        }

        strBuffer.Printf(
            wxT(" %s%s %d.%02d %s"),
            state_result->project->anonymous_platform?_("Local: "):wxT(""),
            strAppBuffer.c_str(),
            state_result->avp->version_num / 100,
            state_result->avp->version_num % 100,
            strClassBuffer.c_str()
        );
    }
}