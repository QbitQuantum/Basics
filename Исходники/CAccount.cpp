bool CAccount::IsPassword(const SString& strPassword, bool* pbUsedHttpPassAppend)
{
    if (pbUsedHttpPassAppend == nullptr)
    {
        return m_Password.IsPassword(strPassword);
    }
    else
    {
        if (m_Password.IsPassword(strPassword))
        {
            *pbUsedHttpPassAppend = false;
            return true;
        }
        else
        {
            SString strPasswordHead = strPassword.Left(strPassword.length() - m_strHttpPassAppend.length());
            SString strPasswordTail = strPassword.Right(m_strHttpPassAppend.length());
            if (m_Password.IsPassword(strPasswordHead) && strPasswordTail == m_strHttpPassAppend)
            {
                *pbUsedHttpPassAppend = true;
                return true;
            }
            return false;
        }
    }
}