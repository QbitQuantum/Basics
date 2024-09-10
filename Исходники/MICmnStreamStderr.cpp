//++ ------------------------------------------------------------------------------------
// Details:	CMICmnStreamStderr destructor.
// Type:	Overridable.
// Args:	None.
// Return:	None.
// Throws:	None.
//--
CMICmnStreamStderr::~CMICmnStreamStderr( void )
{
    Shutdown();
}