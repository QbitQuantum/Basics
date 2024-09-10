void main(void)
{
    char string [] = "Biblia do Programador C/C++, do Jamsa!";
    int i;

    for (i = 0; string [i]; i++)
        putchar (tolower (string [i]));
    putchar ('\n');
    for (i = 0; string [i]; i++)
        putchar (_tolower (string [i]));
    putchar ('\n');
}