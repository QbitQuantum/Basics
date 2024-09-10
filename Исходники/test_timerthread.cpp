int main(int argc, const char *argv[])
{
    TimerThread t;
    t.setTimer(3,1);
    t.setTimerCallback(&func);

    t.startTimerThread();

    sleep(10);
    t.cancelTimerThread();
    return 0;
}