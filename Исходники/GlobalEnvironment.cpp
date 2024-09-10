sGlobalEnvironment::~sGlobalEnvironment( )
{
    if( !m_pNetManager->IsEmpty( ) )
    {
        OutputDebugString( L"[WSocket] you need to shutdown all networks before closing!" );
        __debugbreak( );
    }
}