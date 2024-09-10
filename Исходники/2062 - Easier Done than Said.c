int main()
{
    char str[100];
    int l,flag,asciiflag,i,c_flag;
    level:
    while((scanf("%s",str))){
    if(strcmp(str,"end")==0)
    break;
    flag=0;
    asciiflag=0;
    c_flag=0;
    l=strlen(str);
    for(i=0;i<l;i++)
    {
        if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u')
        {
            flag++;
        }
        if(str[i]==str[i-1])
        {
            c_flag++;
            if(c_flag>1){
            printf("<%s> is not acceptable.\n",str);
            goto level;
            }
        }
        if(str[i]==toascii(str[i])+1)
        {
            asciiflag++;
            if(asciiflag==2) {
                printf("<%s> is not acceptable.\n",str);
                goto level;
            }
        }

    }
    if(flag>0&&c_flag==0&&asciiflag<2) printf("<%s> is acceptable.\n",str);
    else printf("<%s> is not acceptable.\n",str);
    }
    return 0;
}