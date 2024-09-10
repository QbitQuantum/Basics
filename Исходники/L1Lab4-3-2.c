int main()
{
    //a = 97
    //z = 122
    //A = 65
    //Z = 90

    char input[50];
    puts("Enter type a single letter");
    gets(input);

    if (isLower(input[0]) == true)
    {
        input[0] -= 32;
    }
    else if (isUpper(input[0]) == true)
    {
        input[0] += 32;
    }
    puts(input);
}