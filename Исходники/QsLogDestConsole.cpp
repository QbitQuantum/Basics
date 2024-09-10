void QsDebugOutput::output( const QString& message )
{
   OutputDebugStringW(reinterpret_cast<const WCHAR*>(message.utf16()));
   OutputDebugStringW(L"\n");
}