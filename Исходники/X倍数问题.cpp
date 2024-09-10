void fun(char* s,int n)
{
    char* p=s;
    int temp,jinwei;
    for(*p=n+'0', jinwei=0;!(*p=='0'&&jinwei==1);p++)
        ((temp = (*p-'0')*n+jinwei)>9)?(*(p+1)=temp%10+'0',jinwei=temp/10):(*(p+1)=temp+'0',jinwei=0);
    *++p='1',*++p='\0';
    _strrev(s);
}