Signal::Signal(int count)
{
    signalCount = count;

    for (int a = 0; a < count; a++)
    {
        signalEvent[a] = CreateEventA(nullptr, false, false, nullptr);
    }
}