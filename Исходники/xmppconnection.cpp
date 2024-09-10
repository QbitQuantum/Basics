void* polling_thread(void* client)
{
    Client* cl = (Client*) client;
    pthread_mutex_lock(&stop_mutex);
    bool run = !stop;
    pthread_mutex_unlock(&stop_mutex);
    
    while(run)
    {
        pthread_mutex_lock(&stop_mutex);
        run = !stop;
        pthread_mutex_unlock(&stop_mutex);
        cl->recv(10);
    }
    pthread_exit(NULL);
}