/*!
This is where the work happens - We grab a copy of what is in 
the put area and send it to the debug window using OutputDebugString.
*/
void Win32StreamBuf::SendToDebugWindow()
{
    if (IsDebuggerPresent() && !buf_.empty())
		::OutputDebugString(buf_.c_str());
}