void SearchThread::DoSearchLineRE(const wxString& line,
                                  const int lineNum,
                                  const int lineOffset,
                                  const wxString& fileName,
                                  const SearchData* data,
                                  TextStatesPtr statesPtr)
{
    wxRegEx& re = GetRegex(data->GetFindString(), data->IsMatchCase());
    size_t col = 0;
    int iCorrectedCol = 0;
    int iCorrectedLen = 0;
    wxString modLine = line;
    if(re.IsValid()) {
        while(re.Matches(modLine)) {
            size_t start, len;
            re.GetMatch(&start, &len);
            col += start;

            // Notify our match
            // correct search Pos and Length owing to non plain ASCII multibyte characters
            iCorrectedCol = clUTF8Length(line.c_str(), col);
            iCorrectedLen = clUTF8Length(line.c_str(), col + len) - iCorrectedCol;
            SearchResult result;
            result.SetPosition(lineOffset + col);
            result.SetColumnInChars((int)col);
            result.SetColumn(iCorrectedCol);
            result.SetLineNumber(lineNum);
            result.SetPattern(line);
            result.SetFileName(fileName);
            result.SetLenInChars((int)len);
            result.SetLen(iCorrectedLen);
            result.SetFlags(data->m_flags);
            result.SetFindWhat(data->GetFindString());

            // Make sure our match is not on a comment
            int position(wxNOT_FOUND);
            bool canAdd(true);

            if(statesPtr) {
                position = statesPtr->LineToPos(lineNum - 1);
                position += iCorrectedCol;
            }

            if(statesPtr && position != wxNOT_FOUND && data->GetSkipComments()) {
                if(statesPtr->states.size() > (size_t)position) {
                    short state = statesPtr->states.at(position).state;
                    if(state == CppWordScanner::STATE_CPP_COMMENT || state == CppWordScanner::STATE_C_COMMENT) {
                        canAdd = false;
                    }
                }
            }

            if(statesPtr && position != wxNOT_FOUND && data->GetSkipStrings()) {
                if(statesPtr->states.size() > (size_t)position) {
                    short state = statesPtr->states.at(position).state;
                    if(state == CppWordScanner::STATE_DQ_STRING || state == CppWordScanner::STATE_SINGLE_STRING) {
                        canAdd = false;
                    }
                }
            }

            result.SetMatchState(CppWordScanner::STATE_NORMAL);
            if(canAdd && statesPtr && position != wxNOT_FOUND && data->GetColourComments()) {
                // set the match state
                if(statesPtr->states.size() > (size_t)position) {
                    short state = statesPtr->states.at(position).state;
                    if(state == CppWordScanner::STATE_C_COMMENT || state == CppWordScanner::STATE_CPP_COMMENT) {
                        result.SetMatchState(state);
                    }
                }
            }

            if(canAdd) {
                m_results.push_back(result);
                m_summary.SetNumMatchesFound(m_summary.GetNumMatchesFound() + 1);
            }

            col += len;

            // adjust the line
            if(line.Length() - col <= 0) break;
            modLine = modLine.Right(line.Length() - col);
        }
    }
}