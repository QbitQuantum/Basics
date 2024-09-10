bool CLR_RT_ParseOptions::Parameter_Integer::Parse( LPCWSTR arg )
{
    if(swscanf_s( arg, L"%d", m_dataPtr ) == 0)
    {
        wprintf( L"Expecting a number for parameter '%s': %s\n\n", m_szName, arg );
        return false;
    }

    return true;
}