bool CACEdit::HandleKey(UINT nChar, bool m_bFromChild)
{
    if (nChar == VK_ESCAPE ||nChar == VK_RETURN)
    {
        m_Liste.ShowWindow(false);
        return true;
    }

    if (nChar == VK_DOWN || nChar == VK_UP
            || nChar == VK_PRIOR || nChar == VK_NEXT
            || nChar == VK_HOME || nChar == VK_END)
    {
        /*
        ** Vers. 1.1
        ** NEW: _MODE_CURSOR_O_LIST_
        */
        if(!m_Liste.IsWindowVisible() && (m_iMode & _MODE_CURSOR_O_LIST_))
        {
            GetWindowText(m_EditText);
            if(m_EditText.IsEmpty())
            {
                m_Liste.CopyList();
                return true;
            }
        }

        if(m_Liste.IsWindowVisible())
        {
            int pos;


            if(m_iMode & _MODE_STANDARD_
                    || m_iMode & _MODE_FILESYSTEM_
                    || m_iMode & _MODE_FS_START_DIR_)
            {
                m_CursorMode = true;

                if(!m_bFromChild)
                    m_EditText = m_Liste.GetNextString(nChar);
                else
                    m_EditText = m_Liste.GetString();

                if(m_iMode & _MODE_FILESYSTEM_)
                {
                    if (m_EditText.Right(1) == _T('\\'))
                        m_EditText = m_EditText.Mid(0,m_EditText.GetLength()-1);
                }

                m_Liste.SelectItem(-1);
                SetWindowText(m_EditText);
                pos = m_EditText.GetLength();

                if(m_iType == _COMBOBOX_)
                {
                    m_pEdit->SetSel(pos,pos,true);
                    m_pEdit->SetModify(true);
                }

                if(m_iType == _EDIT_)
                {
                    ((CEdit*)this)->SetSel(pos,pos,true);
                    ((CEdit*)this)->SetModify(true);
                }

                GetParent()->SendMessage(ENAC_UPDATE, WM_KEYDOWN, GetDlgCtrlID());
                m_CursorMode = false;
                return true;
            }

            if(m_iMode & _MODE_SEPARATION_)
            {
                CString m_Text,m_Left,m_Right;
                int left,right,pos2=0,len;

                m_CursorMode = true;

                GetWindowText(m_EditText);

                if(m_iType == _EDIT_)
                    pos2 = LOWORD(((CEdit*)this)->CharFromPos(GetCaretPos()));

                if(m_iType == _COMBOBOX_)
                    pos2 = m_pEdit->CharFromPos(m_pEdit->GetCaretPos());

                left  = FindSepLeftPos(pos2-1,true);
                right = FindSepRightPos(pos2);

                m_Text = m_EditText.Left(left);

                if(!m_bFromChild)
                    m_Text += m_Liste.GetNextString(nChar);
                else
                    m_Text += m_Liste.GetString();

                m_Liste.SelectItem(-1);
                m_Text += m_EditText.Mid(right);
                len = m_Liste.GetString().GetLength();

                m_Text += this->m_SeparationStr;

                SetWindowText(m_Text);
                GetParent()->SendMessage(ENAC_UPDATE, WM_KEYDOWN, GetDlgCtrlID());

                right = FindSepLeftPos2(pos2-1);
                left -= right;
                len += right;

                left+=m_SeparationStr.GetLength();

                if(m_iType == _EDIT_)
                {
                    ((CEdit*)this)->SetModify(true);
                    ((CEdit*)this)->SetSel(left+len,left+len,false);
                }

                if(m_iType == _COMBOBOX_)
                {
                    m_pEdit->SetModify(true);
                    m_pEdit->SetSel(left,left+len,true);
                }

                m_CursorMode = false;
                return true;
            }
        }
    }
    return false;
}