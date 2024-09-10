void TestRunnerDlg::addListEntry(const std::string& type, TestResult *result, Test *test, CppUnitException *e)
{
    char        stage [80];
    LV_ITEM     lvi;
    CListCtrl   *listCtrl       = (CListCtrl *)GetDlgItem (IDC_LIST);
    int         currentEntry    = result->testErrors () + result->testFailures () -1;

    sprintf (stage, "%s", type.c_str ());

    lvi.mask        = LVIF_TEXT;
    lvi.iItem       = currentEntry;
    lvi.iSubItem    = 0;
    lvi.pszText     = stage;
    lvi.iImage      = 0;
    lvi.stateMask   = 0;
    lvi.state       = 0;

    listCtrl->InsertItem (&lvi);

    // Set class string
    listCtrl->SetItemText (currentEntry, 1, test->toString ().c_str ());

    // Set the asserted text
    listCtrl->SetItemText(currentEntry, 2, e->what ());

    // Set the line number
    if (e->lineNumber () == CppUnitException::CPPUNIT_UNKNOWNLINENUMBER)
        sprintf (stage, "<unknown>");
    else
        sprintf (stage, "%ld", e->lineNumber ());

    listCtrl->SetItemText(currentEntry, 3, stage);

    // Set the file name
    listCtrl->SetItemText(currentEntry, 4, e->fileName ().c_str ());

    listCtrl->RedrawItems (currentEntry, currentEntry);
    listCtrl->UpdateWindow ();

}