int main(int argc, string argv[])
{   
    // if the user did not include a key in the command line then return an error
    if (argc != 2)
    {
        printf("Usage: ./asciimath key\n");
        return 1;
    }
    
    int key = atoi(argv[1]); 
    string plaintext = GetString();
    
    //  loop to encrypt each character in plaintext 
    for (int i = 0, n = strlen(plaintext); i < n; i++)
        printf("%c", encrypt(key, plaintext[i]));
    
    printf("\n");
        
    return 0;
}