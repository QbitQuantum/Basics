FxInterruptThreadpool::~FxInterruptThreadpool()
{
    //
    // close pool 
    //
    if (m_Pool != NULL) {
        CloseThreadpool(m_Pool);
        m_Pool = NULL;
    }
    
    DestroyThreadpoolEnvironment(&m_CallbackEnvironment);
}