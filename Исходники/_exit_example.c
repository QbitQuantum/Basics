int main(void)
{
    printf("Enter main()\n");
    atexit(f1);
    atexit(f2);
    fflush(stdout);     /* _Exit does not flush unwritten buffered data */
    _Exit(0);
}