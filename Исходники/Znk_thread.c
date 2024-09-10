Znk_INLINE int waitEnd( ZnkThreadInfo thinfo )
{
	int result = (int)WaitForSingleObject( (HANDLE)thinfo->handle_, INFINITE ); 
	closeHandle( thinfo );
	return result;
}