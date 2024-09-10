/////////////////////////////////////////////////////////
// Demonstrate:
// IADsPropertyList::GetPropertyItem
// IADsPropertyEntry
//
void CDlgIADsPropertyList::OnGet()
{

    HRESULT hr;
    CString s;
    BSTR    bstr;
    VARIANT var;
    IDispatch *pDispatch;
    IADsPropertyEntry *pEntry;
    IADsPropertyValue *pValue;
    LONG  lADsType;


    UpdateData(TRUE);
    m_cValueList.ResetContent();

    bstr = m_sAttribute.AllocSysString();
    hr = m_pPropList->GetPropertyItem( bstr, m_cADsType.GetCurSel()+1, &var );
    SysFreeString( bstr );


    if ( SUCCEEDED(hr) )
    {
        pDispatch = V_DISPATCH( &var );
        hr = pDispatch->QueryInterface( IID_IADsPropertyEntry, (void**) &pEntry );
        VariantClear( &var );

        // IADsPropertyEntry
        if ( SUCCEEDED(hr) )
        {
            CPtrList dList;

            // get_Values return array of VT_DISPATH
            hr = pEntry->get_Values( &var );


            pEntry->get_ADsType( &lADsType);

            hr = VariantToPtrList( var, dList );

            pEntry->Release();

            ////////////////////////////
            // IADsPropertyValue
            /////////////////////////////
            if ( SUCCEEDED(hr) )
            {
                POSITION pos;
                pos = dList.GetHeadPosition();
                while ( pos != NULL )
                {
                    pDispatch = (IDispatch*) dList.GetAt(pos);
                    hr = pDispatch->QueryInterface( IID_IADsPropertyValue, (void**) &pValue );

                    if ( SUCCEEDED(hr) )
                    {
                        pValue->AddRef();
                        hr = PropertyValueToString( lADsType, pValue, s );
                        m_cValueList.AddString( s );
                        pValue->Release();
                    }
                    dList.GetNext(pos);
                }

            }

            dList.RemoveAll();
            VariantClear(&var);

        }

    }
}