void timer_change_notify(unsigned long next)
{
    long ticks;

    ticks = next - GETTICKCOUNT();
    if (ticks <= 0)
        ticks = 1;

    qPutty->timerChangeNotify(ticks,next);
}