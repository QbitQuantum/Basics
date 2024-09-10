void KCMKonsole::save()
{
    if(dialog->SchemaEditor1->isModified())
    {
        dialog->TabWidget2->showPage(dialog->tab_2);
        dialog->SchemaEditor1->querySave();
    }

    if(dialog->SessionEditor1->isModified())
    {
        dialog->TabWidget2->showPage(dialog->tab_3);
        dialog->SessionEditor1->querySave();
    }

    KConfig config("konsolerc");
    config.setDesktopGroup();

    config.writeEntry("TerminalSizeHint", dialog->terminalSizeHintCB->isChecked());
    bool bidiNew = dialog->bidiCB->isChecked();
    config.writeEntry("EnableBidi", bidiNew);
    config.writeEntry("MatchTabWinTitle", dialog->matchTabWinTitleCB->isChecked());
    config.writeEntry("WarnQuit", dialog->warnCB->isChecked());
    config.writeEntry("CtrlDrag", dialog->ctrldragCB->isChecked());
    config.writeEntry("CutToBeginningOfLine", dialog->cutToBeginningOfLineCB->isChecked());
    config.writeEntry("AllowResize", dialog->allowResizeCB->isChecked());
    bool xonXoffNew = dialog->xonXoffCB->isChecked();
    config.writeEntry("XonXoff", xonXoffNew);
    config.writeEntry("BlinkingCursor", dialog->blinkingCB->isChecked());
    config.writeEntry("has frame", dialog->frameCB->isChecked());
    config.writeEntry("LineSpacing", dialog->line_spacingSB->value());
    config.writeEntry("SilenceSeconds", dialog->silence_secondsSB->value());
    config.writeEntry("wordseps", dialog->word_connectorLE->text());

    config.writeEntry("schema", dialog->SchemaEditor1->schema());

    config.sync();

    emit changed(false);

    DCOPClient *dcc = kapp->dcopClient();
    dcc->send("konsole-*", "konsole", "reparseConfiguration()", QByteArray());
    dcc->send("kdesktop", "default", "configure()", QByteArray());
    dcc->send("klauncher", "klauncher", "reparseConfiguration()", QByteArray());

    if(xonXoffOrig != xonXoffNew)
    {
        xonXoffOrig = xonXoffNew;
        KMessageBox::information(this, i18n("The Ctrl+S/Ctrl+Q flow control setting will only affect "
                                            "newly started Konsole sessions.\n"
                                            "The 'stty' command can be used to change the flow control "
                                            "settings of existing Konsole sessions."));
    }

    if(bidiNew && !bidiOrig)
    {
        KMessageBox::information(this, i18n("You have chosen to enable "
                                            "bidirectional text rendering by "
                                            "default.\n"
                                            "Note that bidirectional text may "
                                            "not always be shown correctly, "
                                            "especially when selecting parts of "
                                            "text written right-to-left. This "
                                            "is a known issue which cannot be "
                                            "resolved at the moment due to the "
                                            "nature of text handling in "
                                            "console-based applications."));
    }
    bidiOrig = bidiNew;
}