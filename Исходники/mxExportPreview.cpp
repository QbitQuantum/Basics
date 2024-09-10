void mxExportPreview::OnProcTerminate (wxProcessEvent & event) {
    _LOG("mxExportPreview::OnProcessTerminate");
    if (pid<=0||!the_process||event.GetPid()!=pid) return;
    int exit_code = event.GetExitCode();
    delete the_process;
    the_process=NULL;
    if (exit_code!=0) {
        SetMessage(_Z("Error al intentar exportar"));
        state=mxEP_NONE;
        return;
    }

    switch(state) {

    case mxEP_NONE: { // no deberia pasar nunca
        return;
    }
    break;

    case mxEP_CHECK: { // estaba armando el psd, ahora exportar
        wxString command;
        command<<config->psexport_command<<_T(" \"")<<temp_filename<<".psd"<<_T("\" \"")<<temp_filename<<".exp"<<_T("\"");
        if (config->lang[LS_BASE_ZERO_ARRAYS]) command<<_T(" --base_zero_arrays=1");
        int lang_id = mxID_FILE_EXPORT_LANG_FIRST+1+combo_lang->GetCurrentSelection();
        command<<" --lang="<<utils->GetExportLangCode(lang_id);

        the_process = new wxProcess(this->GetEventHandler());
        _LOG("mxExportPreview, command="<<command);
        pid = wxExecute(command,wxEXEC_ASYNC,the_process);
        state = mxEP_EXP;

    }
    break;

    case mxEP_EXP: { // estaba exportando, mostrar
        state = mxEP_NONE;
        code_ctrl->LoadFile(temp_filename+".exp");
    }
    break;

    case mxEP_UPDATE: {  // se interrumpio lo que estaba haciendo para empezar otra vez
        pid = 0;
        state = mxEP_NONE;
        UpdatePrev();
    }
    break;

    default:
        break;
    }
}