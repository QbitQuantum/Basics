int main()
{
    struct timespec ts;

    if( timespec_get( &ts, TIME_UTC) != 0)
        printf("The exact local time:\n"
               "%.24s and %09lu nanoseconds\n", ctime(&ts.tv_sec), ts.tv_nsec);

    return 0;
}