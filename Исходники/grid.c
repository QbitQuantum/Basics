int isCube(unsigned long long int c)
{
    unsigned long long int root=llroundl(cbrtl((long double)c));

    if(c==root*root*root)
	return 1;
    else
	return 0;
}