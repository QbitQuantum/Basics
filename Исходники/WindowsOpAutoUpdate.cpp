VOID CALLBACK WindowsOpAutoUpdatePI::PackageExtractor::WaitOrTimerCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
    g_thread_tools->PostMessageToMainThread(MSG_AUTOUPDATE_UNPACKING_COMPLETE, (MH_PARAM_1)lpParameter, NULL);

    PackageExtractor* pkg_ext = (PackageExtractor*)lpParameter;

    UnregisterWait(pkg_ext->m_wait_object);

    CloseHandle(pkg_ext->m_process_handle);

    delete pkg_ext;
}