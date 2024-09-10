unsigned APIENTRY LibMain( unsigned hmod, unsigned termination )
{
    if( !termination )
    {
        getSGID();

        strcpy( m_szPipeName, PIPE_KSHELL_VIOSUB_BASE );
        _ultoa( m_ulSGID, m_szPipeName + strlen( m_szPipeName ), 16 );
    }

    return 1;
}