void vLoggerConsole(const QString& message)
{
   OutputDebugStringW(reinterpret_cast<const WCHAR*>(message.utf16()));
}