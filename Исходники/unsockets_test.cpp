void * client(void *)
{
    UnixSocket * local = new UnixSocket();
    local->Connect("/tmp/test.sock");
    CHECK_TEXT(local->IsOk(), "Client should connect");
    
    int buffer[1];

    CHECK_TEXT(local->Recv(buffer, sizeof(int)) == sizeof(int), "Should receive a buffer");
    CHECK(local->IsOk());

    buffer[0]++;

    CHECK_TEXT(local->Send(buffer, sizeof(int)) == sizeof(int), "Should send a buffer");
    CHECK(local->IsOk());

    local->Close();
    CHECK_TEXT(local->IsOk(), "Client should close connection");

    delete local;
    pthread_exit(NULL);
}