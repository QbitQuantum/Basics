// wxExecute implementation
//
long wxExecute(wxChar **argv, int flags, wxProcess *process,
               const wxString* cwd, const wxEnvVariableHashMap* env)
{
#if wxUSE_STREAMS
    const int STDIN = 0;
    const int STDOUT = 1;
    const int STDERR = 2;

    wxRedirectableFd in(STDIN), out(STDOUT), err(STDERR);
    bool redirect = process && process->IsRedirected() && (flags & wxEXEC_SYNC);

    if (redirect)
    {
        // close stdin/out/err and reopen them as files
        if (!in.Reopen(wxT("NUL"), O_RDONLY | O_TEXT))
            return -1;

        if (!out.Reopen(wxFileName::CreateTempFileName(wxT("out")),
                        O_CREAT | O_WRONLY | O_TRUNC | O_TEXT))
            return -1;

        if (!err.Reopen(wxFileName::CreateTempFileName(wxT("err")),
                        O_CREAT | O_WRONLY | O_TRUNC | O_TEXT))
            return -1;
    }
#endif // wxUSE_STREAMS

    // FIXME: suspend/resume gui
    int mode = flags & wxEXEC_SYNC ? P_WAIT : P_NOWAIT;
    int result = spawnvp(mode, argv[0], argv);

    if (result == -1)
    {
        wxLogSysError(_("can't execute '%s'"), argv[0]);
    }

#if wxUSE_STREAMS
    if (redirect)
        process->SetPipeStreams(new wxTempFileInStream(out.Release()),
                                new wxFFileOutputStream(wxT("NUL"), wxT("wt")),
                                new wxTempFileInStream(err.Release()));
#endif // wxUSE_STREAMS

    return result;
}