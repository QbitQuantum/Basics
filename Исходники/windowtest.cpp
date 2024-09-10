void WindowTestCase::Mouse()
{
    wxCursor cursor(wxCURSOR_CHAR);
    m_window->SetCursor(cursor);

    CPPUNIT_ASSERT(m_window->GetCursor().IsOk());

    //A plain window doesn't have a caret
    CPPUNIT_ASSERT(!m_window->GetCaret());

    wxCaret* caret = new wxCaret(m_window, 16, 16);
    m_window->SetCaret(caret);

    CPPUNIT_ASSERT(m_window->GetCaret()->IsOk());

    m_window->CaptureMouse();

    CPPUNIT_ASSERT(m_window->HasCapture());

    m_window->ReleaseMouse();

    CPPUNIT_ASSERT(!m_window->HasCapture());
}