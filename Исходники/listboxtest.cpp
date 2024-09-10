void ListBoxTestCase::ClickNotOnItem()
{
#if wxUSE_UIACTIONSIMULATOR
    wxTestableFrame* frame = wxStaticCast(wxTheApp->GetTopWindow(),
                                              wxTestableFrame);

    EventCounter selected(frame, wxEVT_LISTBOX);
    EventCounter dclicked(frame, wxEVT_LISTBOX_DCLICK);

    wxUIActionSimulator sim;

    wxArrayString testitems;
    testitems.Add("item 0");
    testitems.Add("item 1");
    testitems.Add("item 2");

    m_list->Append(testitems);

    // It is important to set a valid selection: if the control doesn't have
    // any, clicking anywhere in it, even outside of any item, selects the
    // first item in the control under GTK resulting in a selection changed
    // event. This is not a wx bug, just the native platform behaviour so
    // simply avoid it by starting with a valid selection.
    m_list->SetSelection(0);

    m_list->Update();
    m_list->Refresh();

    sim.MouseMove(m_list->ClientToScreen(wxPoint(m_list->GetSize().x - 10, m_list->GetSize().y - 10)));
    wxYield();

    sim.MouseClick();
    wxYield();

    sim.MouseDblClick();
    wxYield();

    //If we are not clicking on an item we shouldn't have any events
    CPPUNIT_ASSERT_EQUAL(0, selected.GetCount());
    CPPUNIT_ASSERT_EQUAL(0, dclicked.GetCount());
#endif
}