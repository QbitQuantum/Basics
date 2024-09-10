long int Get_integer()
{
    long int ret;
    Ip = (long int *)malloc(sizeof(long int));
    Printf("Enter an integer:   ");
    Scanf("%ld", Ip);
    ret = *Ip;
    free(Ip);
    return ret;
}