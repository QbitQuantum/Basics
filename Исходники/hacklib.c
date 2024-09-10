char *
sitoa(int n)		/* make a signed digit string from a number */
      
{
    Static char buf[13];

    Sprintf(buf, (n < 0) ? "%d" : "+%d", n);
    return buf;
}