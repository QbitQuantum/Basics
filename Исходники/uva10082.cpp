int main()
{
    int c = getchar();
    do
    {
        int d = c;
        switch (c)
        {
        case '1':
            d = '`';
            break;
        case '2':
            d = '1';
            break;
        case '3':
            d = '2';
            break;
        case '4':
            d = '3';
            break;
        case '5':
            d = '4';
            break;
        case '6':
            d = '5';
            break;
        case '7':
            d = '6';
            break;
        case '8':
            d = '7';
            break;
        case '9':
            d = '8';
            break;
        case '0':
            d = '9';
            break;
        case '-':
            d = '0';
            break;
        case '=':
            d = '-';
            break;

        case 'W':
            d = 'Q';
            break;
        case 'E':
            d = 'W';
            break;
        case 'R':
            d = 'E';
            break;
        case 'T':
            d = 'R';
            break;
        case 'Y':
            d = 'T';
            break;
        case 'U':
            d = 'Y';
            break;
        case 'I':
            d = 'U';
            break;
        case 'O':
            d = 'I';
            break;
        case 'P':
            d = 'O';
            break;
        case '[':
            d = 'P';
            break;
        case ']':
            d = '[';
            break;
        case '\\':
            d = ']';
            break;

        case 'S':
            d = 'A';
            break;
        case 'D':
            d = 'S';
            break;
        case 'F':
            d = 'D';
            break;
        case 'G':
            d = 'F';
            break;
        case 'H':
            d = 'G';
            break;
        case 'J':
            d = 'H';
            break;
        case 'K':
            d = 'J';
            break;
        case 'L':
            d = 'K';
            break;
        case ';':
            d = 'L';
            break;
        case '\'':
            d = ';';
            break;

        case 'X':
            d = 'Z';
            break;
        case 'C':
            d = 'X';
            break;
        case 'V':
            d = 'C';
            break;
        case 'B':
            d = 'V';
            break;
        case 'N':
            d = 'B';
            break;
        case 'M':
            d = 'N';
            break;
        case ',':
            d = 'M';
            break;
        case '.':
            d = ',';
            break;
        case '/':
            d = '.';
            break;
        }
        putchar(d);
        c = getchar();
    } while (c != EOF);

    return 0;
}