int main(int argc, char* argv[])
{
    //stops the program if there are no command line arguments
    if (argc != 2)
    {
        printf("You must enter an argument.\n");
        return 1;
    }
    
    else
    {
        //key is changed to integer
        int k = atoi(argv[1]);
        printf("Enter a string you would like to encrypt with Caesar's cipher: \n");
        //gets the string from the user that we would like to encrypt
        char* s = GetString();
        char cipheredNum;
        int result;
        
        //loops through each char of the string
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            //if the char is a capital or lowercase letter
            if (capital(s[i]) == 1 || lowerCase(s[i]) == 1)
            {
                //change to alphanumeric value, run the cipher, then change back to ascii
                int alphaNum = toAlpha(s[i]);
                cipheredNum = cipher(alphaNum, k);
                result = toAscii(cipheredNum);
            }
            //if the char is neither capital or lowercase, it stays the same
            else
                result = s[i];
            //prints the ciphered char before moving on to next char
            printf("%c", result);
        }
        printf("\n");
        return 0;
    }
}