void RichEditHost::SetMaxLength(uint nMaxLength)
{
    if (m_dwMaxLength != nMaxLength)
    {
        m_dwMaxLength = nMaxLength;
        if (m_pTextServices)
        {
            CComBSTR bsText;
            if (m_pTextServices)
            {
                m_pTextServices->TxGetText(&bsText);
                if (bsText.Length() > 0)
                {
                    wstring wstrText = bsText;
                    if (wstrText.length() > m_dwMaxLength)
                    {
                        wstrText.erase(wstrText.begin() + m_dwMaxLength, wstrText.end());
                        m_pTextServices->TxSetText(wstrText.c_str());
                    }
                }
            }

            LRESULT lRes = 0;
            HRESULT hr = m_pTextServices->TxSendMessage(EM_EXLIMITTEXT, 0, nMaxLength, &lRes);
            hr = m_pTextServices->OnTxPropertyBitsChange(TXTBIT_MAXLENGTHCHANGE, TXTBIT_MAXLENGTHCHANGE);
        }
    }
}