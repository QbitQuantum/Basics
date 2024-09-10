int FileStream::PrintF( const char* Str, ... ) const
{
	ASSERT( m_FileMode == EFM_Write || m_FileMode == EFM_Append );

	va_list	Args;
	int		Length	= 0;
	char*	Buffer	= NULL;
	int		RetVal	= 0;

	va_start( Args, Str );
	Length = VSPRINTF_COUNT( Str, Args ) + 1;
	Buffer = new char[ Length ];	// TODO: Pool this instead of dynamically allocating
	VSPRINTF( Buffer, Length, Str, Args );

	RetVal = Write( Length - 1, Buffer );

	SafeDelete( Buffer );
	return RetVal;
}