int main()
{
    char *str = new char[9];
    str[0] = ' ';
    str[1] = ' ';
    str[2] = ' ';
    str[3] = ' ';
    str[4] = '+';
    str[5] = '3';
    str[6] = '2';
    str[7] = '1';
    str[8] = '\0';
//     char *str = new char[1];
//     str[0] = '\0';
    Solution mySolution;
    int out = mySolution.atoi(str);

    printf("%d\n", out);
}