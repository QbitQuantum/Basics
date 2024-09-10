void Out(int a)
{
    if(a>9)
        Out(a/10);
    putchar(a%10+'0');
}