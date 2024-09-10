bool KileScriptDocument::isSpace(int line, int column)
{
    return isSpace(KTextEditor::Cursor(line,column));
}