void os_set_line_buffering(void)
{
    setvbuf(stdout, NULL, _IOLBF, 0);
}