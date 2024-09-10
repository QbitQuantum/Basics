/*
 * Destructor
 */
JIntellitypeHandler::~JIntellitypeHandler()
{
	// Get field ID
	jfieldID l_handlerId = g_JIntellitypeThread.m_env->GetFieldID( g_JIntellitypeThread.m_env->GetObjectClass( m_object ), "handler", "I" );

	// Set field
	g_JIntellitypeThread.m_env->SetIntField( m_object, l_handlerId, 0 );

	// Release our reference
	g_JIntellitypeThread.m_env->DeleteGlobalRef( m_object );
	
	// unregister the shell hook
	DeregisterShellHookWindow( m_window );

	// Destroy window
	DestroyWindow( m_window );
}