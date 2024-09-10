bool Project_Engine::Parse_Str_Float(wchar_t* Text_Buffer, int Line_length, int &nPosition, float& fValue)
{
    wchar_t pwzNumber[20];
    bool bResult = ReadNumber(Text_Buffer, Line_length, nPosition, pwzNumber);
    fValue = (bResult) ? (float)_wtof(pwzNumber) : 0;
    return false;
}