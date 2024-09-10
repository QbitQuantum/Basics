//
// Function: AssignToFreeThread
//
// Description:
//    This routine assigns a socket connection to an available child
//    thread to handle any IO on it. If no threads are available, a 
//    new thread is spawned to handle the connection.
//
void AssignToFreeThread(SOCKET_OBJ *sock)
{
    THREAD_OBJ *thread=NULL;

    thread = gChildThreads;
    while (thread)
    {
        // If this routine returns something other than SOCKET_ERROR
        //    that it was successfully assigned to a child thread.
        if (InsertSocketObj(thread, sock) != SOCKET_ERROR)
            break;
        thread = thread->next;
    }

    if (thread == NULL)
    {
        // No thread was found to assign the client socket to, create a new thread
        //
        printf("Creating new thread object\n");

        thread = GetThreadObj();

        thread->Thread = CreateThread(NULL, 0, ChildThread, (LPVOID)thread, 0, NULL);
        if (thread->Thread == NULL)
        {
            fprintf(stderr, "AssignToFreeThread: CreateThread failed: %d\n", GetLastError());
            ExitProcess(-1);
        }

        InsertSocketObj(thread, sock);

        // Insert the thread the list of threads
        if (gChildThreads == NULL)
        {
            gChildThreads = thread;
        }
        else
        {
            thread->next = gChildThreads;
            gChildThreads = thread;
        }

        gChildThreadsCount++;

    }
 
    // signal child thread to rebuild the event list
    WSASetEvent(thread->Event);

    return;
}