int IsPalindrome(int num)
{
    char *str = (char *) malloc(2*DIGITS);
    //printf("IsPalindrome num = %d\n",num);
    Itoa(num, str);
    int len = strlen(str);
    
    //printf("IsPalindrome str = %s\n",str);
    int start = 0;
    int end = len-1; 
    
    while(start < end)
    {
        if(str[start] != str[end])
        {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}