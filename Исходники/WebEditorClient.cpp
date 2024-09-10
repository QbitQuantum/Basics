void WebEditorClient::checkSpellingOfString(StringView text, int* misspellingLocation, int* misspellingLength)
{
    *misspellingLocation = -1;
    *misspellingLength = 0;

    COMPtr<IWebEditingDelegate> ed;
    if (FAILED(m_webView->editingDelegate(&ed)) || !ed.get())
        return;

    initViewSpecificSpelling(m_webView);
    ed->checkSpellingOfString(m_webView, text.upconvertedCharacters(), text.length(), misspellingLocation, misspellingLength);
}