//销毁编辑框//
void CNewConfigGraChiDlg::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
    CString strEditData;
    float tempfloat;
    int nTempData;
    distroyedit->GetWindowText(strEditData);
    strEditData = strEditData.Trim();
    if (strEditData.IsEmpty())             //如果输入为空，则销毁编辑框//
    {
        distroyedit->DestroyWindow();
        m_vectList2[Item].m_fSetValue = -3001;
        list->SetItemText(Item, 3, _T(""));
        return;
    }
    if (m_vectList2[Item].m_ValueType == 0 && (strEditData != _T("0") && strEditData != _T("1")))
    {
        AfxMessageBox(_T("非法操作，该参数值只能为“0”或“1”！"));
        distroyedit->DestroyWindow();                          //销毁对象//
        return;
    }
    if (strEditData == strEditData.SpanIncluding(_T("0123456789.")))
    {
        switch (m_vectList2[Item].m_ValueType)
        {
        case 0:
            if (strEditData==_T("0"))
            {
                m_vectList2[Item].m_fSetValue = 0;
                list->SetItemText(Item, 3, _T("0"));
            }
            else
            {
                m_vectList2[Item].m_fSetValue = 1;
                list->SetItemText(Item, 3, _T("1"));
            }
            break;
        case 1:
        case 2:
        case 3:
            nTempData = (float)_wtof(strEditData);
            m_vectList2[Item].m_fSetValue = nTempData;    //将修改后的值存入容器//
            strEditData.Format(_T("%d"), nTempData);
            list->SetItemText(Item, 3, strEditData);      //将修改写入列表框//
            break;
        case 4:
        case 5:
            tempfloat = (float)_wtof(strEditData);
            strEditData.Format(_T("%.2f"), tempfloat);
            list->SetItemText(Item, 3, strEditData);      //将修改写入列表框//
            m_vectList2[Item].m_fSetValue = tempfloat;    //将修改后的值存入容器//
            break;
        default:
            break;
        }
    }
    else
        AfxMessageBox(_T("非法操作，请输入数字！"));
    distroyedit->DestroyWindow();                          //销毁对象//
}