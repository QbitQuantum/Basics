void
CIBusWinHandler::commit(const TWCHAR* wstr)
{
    if (wstr) {
        std::wstring str;
        copy(wstr, wstr+WCSLEN(wstr)+1, back_inserter(str));
        m_engine->commit_string(str);
    }
}