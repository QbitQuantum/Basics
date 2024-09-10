////////////////////////////////////////////////////////////////
//
// CShaderItem::SetValue
//
// Set one bool
//
////////////////////////////////////////////////////////////////
bool CShaderItem::SetValue ( const SString& strName, bool bValue )
{
    if ( D3DXHANDLE* phParameter = MapFind ( m_pEffectWrap->m_valueHandleMap, strName.ToUpper () ) )
    {
        // Check if value is changing
        if ( !m_pShaderInstance->CmpBoolValue( *phParameter, bValue ) )
        {
            // Check if we need a new shader instance
            MaybeRenewShaderInstance ();
            m_pShaderInstance->SetBoolValue( *phParameter, bValue );
        }
        return true;
    }
    return false;
}