int main()
{
    char* str1 = malloc(sizeof(char) * 10); 
    strcpy(str1, "efgh");
    char* str2 = malloc(sizeof(char) * 10); 
    strcpy(str2, "abcd");
   
    strcat_m(str2, str1); 
    printf("%s\n", str2); // expect abcdefgh 
    char* rev_str1 = strrev(str1); 
    printf("%s\n", rev_str1); // expect hgfe
    
    free(str1); free(str2); free(rev_str1);  
    return 0;
}