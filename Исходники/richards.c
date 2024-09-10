void RBench::InitTrace()
{   char c;

    printf("Trace (y/n)? ");
    c = getchar();
    tracing = (_toupper(c) == 'Y');
}