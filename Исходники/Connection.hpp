inline connection::~connection()
{
    socket_m.close();
    
    read_thread_m.join();
    send_thread_m.join();
}