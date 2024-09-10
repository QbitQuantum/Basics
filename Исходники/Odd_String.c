int main()
{
    char str[20],str1[20];
    scanf("%s",str);
    strcpy(str1,str);
    strrev(str1);
    int i,j,n,k=0,l=0;
    n=strlen(str);
    char res[n][n];
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==(n/2)&&j==(n/2))
            {
                res[i][j]=str[k];
                k++;
                l++;
            }
            else if(i==j)
            {
                res[i][j]=str[k];
                k++;
            }
            else if((n-1-i)==j)
            {
                res[i][j]=str1[l];
                l++;
            }

            else
            {
                res[i][j]=NULL;
            }
        }
    }
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                printf("%c  ",res[i][j]);
            }
            printf("\n");
        }
    return 0;
}