void
suspend(int s)
{
    suspended = s;
    if (suspended)
        setcursor(mousectl, &whitearrow);
    else
        setcursor(mousectl, nil);
    if (!suspended)
        drawpiece();
    drawboard();
    flushimage(display, 1);
}