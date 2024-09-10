BOOL CDialogOption::OnInitDialog() {
    CString ak;
    CString sk;
    CString host;
    ConfigMgr::Instance().GetAk(ak);
    ConfigMgr::Instance().GetSk(sk);
    ConfigMgr::Instance().GetHost(host);

    AES aes;

    aes.Decrypt(ak, ak);
    aes.Decrypt(sk, sk);

    m_strAK = m_strAKbak = ak;
    m_strSK = m_strSKbak = sk;
    m_strHost = m_strHostbak = host;

    CDialog::OnInitDialog();
    return TRUE;
}