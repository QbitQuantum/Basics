void* protocolManagerAsynchronousUpdate(void* data)
{
    ProtocolManager* manager = static_cast<ProtocolManager*>(data);
    manager->m_asynchronous_thread_running = true;
    while(manager && !manager->exit())
    {
        manager->asynchronousUpdate();
        StkTime::sleep(2);
    }
    manager->m_asynchronous_thread_running = false;
    return NULL;
}