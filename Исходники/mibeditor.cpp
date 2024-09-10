void MibEditor::Find(bool reevaluate)
{
    QTextCursor tc;

    if (reevaluate)
    {
        ff = 0;
        find_string = find_uid.comboFind->currentText();
        if (!find_strings.contains(find_string))
            find_strings.append(find_string);

        if (find_uid.checkWords->isChecked())
            ff |= QTextDocument::FindWholeWords;
        if (find_uid.checkCase->isChecked())
            ff |= QTextDocument::FindCaseSensitively;
        if (find_uid.checkBackward->isChecked())
            ff |= QTextDocument::FindBackward;
    }

    tc = s->MainUI()->MIBFile->document()->find(find_string, 
                                                s->MainUI()->MIBFile->textCursor(), 
                                                ff);

    if (!tc.isNull())
    {
        s->MainUI()->MIBFile->setTextCursor(tc);
        tc.select(QTextCursor::WordUnderCursor);
    }
}