int main(int argc, char* argv[])
{
    esReport("This is the upcall test server process.\n");

    // System()->trace(true);

    Handle<es::Context> nameSpace = System()->getRoot();
    Handle<es::CurrentThread> currentThread = System()->currentThread();

    // create server
    TestServer* server = new TestServer;

    // register this console.
    Handle<es::Context> device = nameSpace->lookup("device");
    ASSERT(device);
    es::Binding* ret = device->bind("testServer", static_cast<es::Stream*>(server));
    ASSERT(ret);
    ret->release();

    while (1 < server->ref)
    {
        currentThread->sleep(10000000LL);
    }

    server->release();

    System()->trace(false);
}