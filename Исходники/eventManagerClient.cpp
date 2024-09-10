int main(int argc, char* argv[])
{
    esReport("This is the Event manager client process.\n");

    // System()->trace(true);
    Handle<es::CurrentThread> currentThread = System()->currentThread();

    Handle<es::Context> nameSpace = System()->getRoot();
    Handle<es::EventQueue> eventQueue = 0;

    while (!eventQueue)
    {
        eventQueue = nameSpace->lookup("device/event");
        currentThread->sleep(10000000 / 60);
    }

    esReport("start client loop.\n");

    unsigned int point;
    int x0;
    int y0;
    int x;
    int y;
    point = eventQueue->getMousePoint();
    x0 = point >> 16;
    y0 = point & 0xffff;
    for (;;)
    {
        if (int stroke = eventQueue->getKeystroke())
        {
            esReport("0x%x\n", stroke);
        }
        point = eventQueue->getMousePoint();
        x = point >> 16;
        y = point & 0xffff;
        if (x != x0 || y != y0)
        {
            x0 = x;
            y0 = y;
            esReport("(%3d, %3d)\n", x0, y0);
        }

        currentThread->sleep(10000000 / 60);
    }

    // System()->trace(false);
}