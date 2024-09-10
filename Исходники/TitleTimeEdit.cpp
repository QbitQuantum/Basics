void CTitleTimeEdit::KeyInUp()
{
    int nCharPos = CharFromPos(GetCaretPos());
    if(nCharPos < 3)
    {
        if(m_szTimeChar[1] < s_szMaxTMChar[1])
            m_szTimeChar[1] ++;
        else if(m_szTimeChar[1] == s_szMaxTMChar[1])
        {
            if(m_szTimeChar[0] < s_szMaxTMChar[0])
            {
                m_szTimeChar[0] ++;
                m_szTimeChar[1] = '0';
            }
        }
    }
    else if(nCharPos < 6)
    {
        if(m_szTimeChar[4] < s_szMaxTMChar[4])
            m_szTimeChar[4] ++;
        else if(m_szTimeChar[4] == s_szMaxTMChar[4])
        {
            if(m_szTimeChar[3] < s_szMaxTMChar[3])
            {
                m_szTimeChar[3] ++;
                m_szTimeChar[4] = '0';
            }
        }
    }
    else if(nCharPos < 9)
    {
        if(m_szTimeChar[7] < s_szMaxTMChar[7])
            m_szTimeChar[7] ++;
        else if(m_szTimeChar[7] == s_szMaxTMChar[7])
        {
            if(m_szTimeChar[6] < s_szMaxTMChar[6])
            {
                m_szTimeChar[6] ++;
                m_szTimeChar[7] = '0';
            }
        }
    }
    else
    {
        if(m_szTimeChar[11] < s_szMaxTMChar[11])
            m_szTimeChar[11] ++;
        else if(m_szTimeChar[11] == s_szMaxTMChar[11])
        {
            if(m_szTimeChar[10] < s_szMaxTMChar[10])
            {
                m_szTimeChar[10] ++;
                m_szTimeChar[11] = '0';
            }
            else if(m_szTimeChar[10] == s_szMaxTMChar[10])
            {
                if(m_szTimeChar[9] < s_szMaxTMChar[9])
                {
                    m_szTimeChar[9] ++;
                    m_szTimeChar[10] = '0';
                    m_szTimeChar[11] = '0';
                }
            }
        }
    }
    Update();
    SetSel(nCharPos, nCharPos);
}