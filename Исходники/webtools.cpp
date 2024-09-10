void WebTools::OnEditorContextMenu(clContextMenuEvent& event)
{
    event.Skip();
    IEditor* editor = m_mgr->GetActiveEditor();
    if(editor && m_jsCodeComplete && IsJavaScriptFile(editor) && !InsideJSComment(editor)) {
        m_jsCodeComplete->AddContextMenu(event.GetMenu(), editor);
    }
}