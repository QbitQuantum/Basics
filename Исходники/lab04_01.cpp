/*
 * Transforma un double in string.
 */
void dtoa(double d, char s[5])
{
    char *str = (char*) malloc(5*sizeof(char));
    int aux1, aux2;
    int aux = (int) d;

    if ((d - aux) > 0.96)
        aux++;

    itoa(aux, str, 10);
    s[0] = str[0];
    s[1] = '.';
    d = d - ((int) d);
    if ((d >= 0.96) || (d <= 0.04))
    {
        s[2] = '0';
        s[3] = '0';
        s[4] = '\0';
    }
    else if ((d > 0.04) && (d <= 0.09))
    {
        s[2] = '0';
        s[3] = '5';
        s[4] = '\0';
    }
    else
    {
        str = (char*) ecvt(d, 2, &aux1, &aux2);
        s[2] = str[0];
        s[3] = str[1];
        s[4] = '\0';
    }
    free(s);
}