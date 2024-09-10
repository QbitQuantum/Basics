int main(void)
{
    int a = -1;
    atexit( nexit);
    at_quick_exit( qexit);

    if( a < 0)
       quick_exit(EXIT_FAILURE);

    return 0;
}