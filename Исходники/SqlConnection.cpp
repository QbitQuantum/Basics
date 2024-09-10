void SqlConnection::AcquireErrorInfo() {
    if (m_mysql != nullptr) {
        const auto errorCode = mysql_errno(m_mysql);
        const auto errorMsg = mysql_error(m_mysql);
        SetErrorInfo(errorCode, errorMsg);
    }
}