int ContextBase::FindNext(const wxString& what, int& pos)
{
    wxStyledTextCtrl* ctrl = GetCtrl().GetCtrl();
    int startpos = ctrl->PositionFromLine(ctrl->GetFirstVisibleLine());
    int lastLine = ctrl->GetFirstVisibleLine() + ctrl->LinesOnScreen();
    int endpos = ctrl->GetLineEndPosition(lastLine);

    if((pos < startpos) || (pos > endpos)) return wxNOT_FOUND;
    int where = ctrl->FindText(pos, endpos, what);
    if(where != wxNOT_FOUND) {
        pos = where + what.length();
    }
    return where;
}