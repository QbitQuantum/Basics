void hex(int a)
{
    int r,i;
    char h[15];
    for(i=0; a>0; i++,a/=16)
    {
        r=a%16;
        if(r<10)
            h[i]=(char)r+48;
        else
            h[i]=(char)r+55;
    }
    h[i]='\0';
    strrev(h);
    puts(h);
}