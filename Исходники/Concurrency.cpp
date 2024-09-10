void C_CondVar::M_SignalOne()
{
#ifdef _WIN32
    WakeConditionVariable(&m_Cond);
#else
    pthread_cond_signal(&m_Cond);
#endif
}