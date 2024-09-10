void CInputWin32::DestroyInputContext( HInputContext context )
{
	assert( context != DEFAULT_INPUT_CONTEXT );
	if ( m_hContext == context )
	{
		ActivateInputContext( DEFAULT_INPUT_CONTEXT );
	}
	m_Contexts.Remove(context);
}