DWORD CCandidateWindow::_GetSelectedCandidateString(_Outptr_result_maybenull_ const WCHAR **ppwchCandidateString)
{
    CCandidateListItem* pItemList = nullptr;

    if (_currentSelection >= _candidateList.size())
    {
        *ppwchCandidateString = nullptr;
        return 0;
    }

    pItemList = &_candidateList[_currentSelection];
    if (ppwchCandidateString)
    {
		*ppwchCandidateString = pItemList->GetChar();
    }
    return (DWORD)wcslen(*ppwchCandidateString);
}