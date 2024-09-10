void CDB_driver::ParseOutput(const wxString& output)
{
    m_Cursor.changed = false;
    static wxString buffer;
    buffer << output << _T('\n');

    m_pDBG->DebugLog(output);

    if (rePrompt.Matches(buffer))
    {
        int idx = buffer.First(rePrompt.GetMatch(buffer));
        cbAssert(idx != wxNOT_FOUND);
        m_ProgramIsStopped = true;
        m_QueueBusy = false;
        DebuggerCmd* cmd = CurrentCommand();
        if (cmd)
        {
            RemoveTopCommand(false);
            buffer.Remove(idx);
            if (buffer[buffer.Length() - 1] == _T('\n'))
                buffer.Remove(buffer.Length() - 1);
            cmd->ParseOutput(buffer.Left(idx));
            delete cmd;
            RunQueue();
        }
    }
    else
        return; // come back later

    bool notifyChange = false;

    // non-command messages (e.g. breakpoint hits)
    // break them up in lines
    wxArrayString lines = GetArrayFromString(buffer, _T('\n'));
    for (unsigned int i = 0; i < lines.GetCount(); ++i)
    {
//            Log(_T("DEBUG: ") + lines[i]); // write it in the full debugger log

        if (lines[i].StartsWith(_T("Cannot execute ")))
        {
            Log(lines[i]);
        }
        else if (lines[i].Contains(_T("Access violation")))
        {
            m_ProgramIsStopped = true;
            Log(lines[i]);
            m_pDBG->BringCBToFront();

            Manager::Get()->GetDebuggerManager()->ShowBacktraceDialog();
            DoBacktrace(true);
            InfoWindow::Display(_("Access violation"), lines[i]);
            break;
        }
        else if (notifyChange)
            continue;

        // Breakpoint 0 hit
        // >   38:     if (!RegisterClassEx (&wincl))
        else if (reBP.Matches(lines[i]))
        {
            m_ProgramIsStopped = true;
            Log(lines[i]);
            // Code breakpoint / assert
            m_pDBG->BringCBToFront();
            Manager::Get()->GetDebuggerManager()->ShowBacktraceDialog();
            DoBacktrace(true);
            break;
        }
        else if (lines[i].Contains(_T("Break instruction exception")) && !m_pDBG->IsTemporaryBreak())
        {
            m_ProgramIsStopped = true;
        	// Code breakpoint / assert
            m_pDBG->BringCBToFront();
            Manager::Get()->GetDebuggerManager()->ShowBacktraceDialog();
            DoBacktrace(true);
            break;
        }
    }

    if (notifyChange)
        NotifyCursorChanged();

    buffer.Clear();
}