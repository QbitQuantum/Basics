int kmp(char s[], int ss, char t[], int ts){
    int h[ts]; //Partial Table
    createTable(t,h,ts);

    int i=0,j=0;
    while(i<ss){    
        while(s[i]!=t[0]) i++;
        j=1;
        while(s[i+j]==t[j]) j++;
        if(j==ts-1) {
            if(DEBUG) { 
                int k = 0;
                for(k=0;k<j;k++)
                    printf("%c",s[i+k]);
                printf("\n");
            }
            return i;
        } else {
            i += j - 1 - h[j-1];
            if(DEBUG) printf("Advance :%d\n",j-1-h[j-1]);
        }
    }

    return -1;
}