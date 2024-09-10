void
foo(unsigned int N, int *x)
{
    unsigned int i = getThreadID();
    if(i < N)
	x[i] = i;
}