int ToDoListView::CalculateLineNumber(const wxString& buffer, int upTo, int &oldline, int &oldlinepos )
{
    for (; oldlinepos < upTo; ++oldlinepos)
    {
        if (buffer.GetChar(oldlinepos) == _T('\r') && buffer.GetChar(oldlinepos + 1) == _T('\n')) // CR+LF
            continue; // we 'll count on \n (next loop)
        else if (buffer.GetChar(oldlinepos) == _T('\r') || // CR only
                buffer.GetChar(oldlinepos) == _T('\n')) // lf only
            ++oldline;
    }
    return oldline;
}