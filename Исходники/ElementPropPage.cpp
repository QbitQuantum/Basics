void CElementPropPage::UpdateControls(IDMGraphCtrl* pGraphCtrl)
{
    ATLASSERT(pGraphCtrl);
    HRESULT hr;
    CComPtr<IDMGraphElement> spElement;
    hr = GetCurrentElement(pGraphCtrl, &spElement);
    BOOL bEnabled = spElement != NULL;
    const UINT idCtrls[] = { IDC_LINE_COLOR, IDC_POINT_COLOR, IDC_LINE_WIDTH, IDC_POINT_WIDTH, IDC_COMBO_TYPE, IDC_COMBO_SYMBOL,
                             IDC_CHECK_VISIBLE, IDC_CHECK_SOLID, IDC_EDIT_NAME, IDC_DELBUTTON,
                             IDC_TXT_E1, IDC_TXT_E2, IDC_TXT_E3, IDC_TXT_E4, IDC_TXT_E5, IDC_TXT_E6, IDC_TXT_E7, IDC_TXT_E8, 0
                           };
    int i;

    for(i=0; idCtrls[i]; ::EnableWindow(GetDlgItem(idCtrls[i++]), bEnabled));

    if(bEnabled == FALSE)
    {
        return;
    }

    OLE_COLOR color;
    COLORREF col;
    hr = spElement->get_LineColor(&color);
    hr = OleTranslateColor(color, NULL, &col);
    m_btnLineColPicker.SetColor(col);
    hr = spElement->get_PointColor(&color);
    hr = OleTranslateColor(color, NULL, &col);
    m_btnPointColPicker.SetColor(col);
    long width;
    hr = spElement->get_LineWidth(&width);
    SetDlgItemInt(IDC_LINE_WIDTH,width);
    hr = spElement->get_PointSize(&width);
    SetDlgItemInt(IDC_POINT_WIDTH,width);
    LineType type;
    hr = spElement->get_Linetype(&type);
    SendDlgItemMessage(IDC_COMBO_TYPE, CB_SETCURSEL, type);
    SymbolType symbol;
    hr = spElement->get_PointSymbol(&symbol);
    SendDlgItemMessage(IDC_COMBO_SYMBOL, CB_SETCURSEL, symbol);
    VARIANT_BOOL visible;
    hr = spElement->get_Show(&visible);
    CheckDlgButton(IDC_CHECK_VISIBLE, visible ? BST_CHECKED : BST_UNCHECKED);
    VARIANT_BOOL solid;
    hr = spElement->get_SolidPoint(&solid);
    CheckDlgButton(IDC_CHECK_SOLID, visible ? BST_CHECKED : BST_UNCHECKED);
    CComBSTR ids;
    hr = spElement->get_Name(&ids);
    ::SetDlgItemTextW(m_hWnd, IDC_EDIT_NAME, ids);
}