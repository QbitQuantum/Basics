Token Token::from_session(const Session& session)
{
    HANDLE h = nullptr;

    if (FALSE != WTSQueryUserToken(static_cast<DWORD>(session.id()), &h)) {
        return std::move(Token(h));
    } 

    throw Poco::SystemException("failed to obtain session token", GetLastError());
}