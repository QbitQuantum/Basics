bool tScriptState::PreprocessCommand(tCommand& cmd, CString& s, bool& bSilent)
{
    bool bAdd = FALSE;
    bool bEnd = FALSE;
    switch (cmd.cmdId)
    {
        case cmdInvalid:
            FailCase("Invalid line: %s", s.GetBuffer());
            break;
        case cmdPreprocess:
            if (!strcmp(cmd.params[0]->String(), "loud"))
                bSilent = FALSE;
            if (!strcmp(cmd.params[0]->String(), "noisy"))
                bSilent = FALSE;
            if (!strcmp(cmd.params[0]->String(), "quiet"))
                bSilent = TRUE;
            break;
        case cmdEnd:
            bEnd = TRUE;
            bAdd = TRUE;
            break;
        case cmdLabel:
            if (FindLabelByName(*cmd.params[0]))
            {
                FailCase("Can't add label %s", cmd.params[0]->String());
            }
            else
            {
                tLabel *newLabel = new tLabel(cmd.params[0]->String(), cmd);
                Labels.AddTail(newLabel);
            }
            bAdd = TRUE;
            break;
        case cmdIf:
            {
                tCommand nestedCommand;
                bool bIsBad;
                CString sNested = cmd.params[1]->String();
                CString sCopy = sNested;
                ParseCommand(sNested, nestedCommand, currentCommandIndex++, bSilent);
                bIsBad = nestedCommand.cmdId == cmdLabel || nestedCommand.cmdId == cmdComment;
                if (bIsBad)
                {
                    FailCase("Invalid nested command %s", (LPCSTR)sCopy);
                }
                else
                {
                    cmd.elseStepForIf = currentCommandIndex;
                    tCommand *pNewCommand = new tCommand(cmd);
                    Commands.Add(pNewCommand);
                    PreprocessCommand(nestedCommand, sCopy, bSilent);
                }
            }
            break;
        default:
            bAdd = TRUE;
            break;
    }

    if (bAdd)
    {
        tCommand *pNewCommand = new tCommand(cmd);
        Commands.Add(pNewCommand);
    }
    return bEnd;
}