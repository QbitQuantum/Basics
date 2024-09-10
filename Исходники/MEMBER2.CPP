void ThreadObject::WaitForExit()
{
    WaitForSingleObject(m_hThread, INFINITE);
    CloseHandle(m_hThread);
}