void MyApp::Log(const wxString& text)
{
    if (GetTopWindow())
    {
        ((MyFrame*) GetTopWindow())->Log(text);
    }
}