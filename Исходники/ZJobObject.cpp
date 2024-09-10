//终止作业
bool ZJobObject::terminate(DWORD exitCode/* = 4*/)
{
    return !!TerminateJobObject(m_handle, exitCode);
}