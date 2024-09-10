void PropertyAdmin::initialize()
{
    if (m_bInitialized)
        return;
    m_bInitialized = true;
    try 
    {
        CComPtr<IPropertyManager> pPropMan;
        if ((pPropMan.p = GET_OPMPROPERTY_MANAGER(m_pClass))==NULL)
            _com_issue_error(E_FAIL);
        _com_util::CheckError(CComObject<CSimpleProperty>::CreateInstance(&m_pSimple));
        m_pSimple->AddRef();
        _com_util::CheckError(CComObject<CCategorizedProperty>::CreateInstance(&m_pCategorized));
        m_pCategorized->AddRef();
        _com_util::CheckError(CComObject<CEnumProperty>::CreateInstance(&m_pEnum));
        m_pEnum->AddRef();
        _com_util::CheckError(pPropMan->AddProperty(m_pSimple));
        _com_util::CheckError(pPropMan->AddProperty(m_pCategorized));
        _com_util::CheckError(pPropMan->AddProperty(m_pEnum));
    }
    catch(const _com_error& )
    {
        uninitialize();                
        acutPrintf("\nSimpleDynProps: initialize failed!!!\n");
        return;
    }
}