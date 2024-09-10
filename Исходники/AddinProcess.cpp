/**
 *\fn           HRESULT GetAllControl(CommandBarControls *pControls, LIST_STR &lstControl)
 *\brief        得到菜单的所有菜单项
 *\param[in]    CommandBarControls * pControls 
 *\param[in]    LIST_STR & lstControl 
 *\return       HRESULT 0成功,其它失败
 */
HRESULT CAddinProcess::GetAllControl(CommandBarControls *pControls, LIST_STR &lstControl)
{
    if (NULL == pControls) return E_INVALIDARG;

    int nCount = 0;
    HRESULT hr = pControls->get_Count(&nCount);

    for (int i = 1; i <= nCount; i++)
    {
        CComPtr<CommandBarControl> pControl; // 菜单Item

        VARIANT varIndex;
        VariantInit(&varIndex);
        varIndex.vt = VT_I4;
        varIndex.lVal = i;
        hr = pControls->get_Item(varIndex, &pControl);

        if (NULL == pControl) continue;

        BSTR bstrName;
        hr = pControl->get_Caption(&bstrName);

        std::string name = BstrToStr(bstrName);

        lstControl.push_back(name);

        AtlTrace("Control: %d %s\n", i, name.c_str());

        /*
        // 得到子菜单
        long nc = 0;
        hr = pControl->get_accChildCount(&nc);

        for (int j = 1; j <= nc; j++)
        {
        VARIANT varIndex;
        VariantInit(&varIndex);
        varIndex.vt = VT_I4;
        varIndex.lVal = j;
        BSTR bstrName1;
        hr = pControl->get_accName(varIndex, &bstrName1);

        CComPtr<IDispatch> pDisp;
        hr = pControl->get_accChild(varIndex, &pDisp);

        CComPtr<CommandBarControl> pSubControl;
        pSubControl = pDisp;

        if (NULL != pSubControl)
        {
        hr = pSubControl->get_Caption(&bstrName1);
        std::string name = BstrToStr(bstrName1);
        AtlTrace("Control:Child %d %s\n", i, name.c_str());
        }
        }
        */
    }

    return hr;
}