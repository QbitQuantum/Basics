void limpiarbuffer(void)
{
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}