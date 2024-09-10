void
foo (char *input)
{
    input = __builtin_assume_aligned (input, 8);
    input[0] = 'H';
    input[1] = 'e';
    input[2] = 'l';
    input[3] = 'l';
    input[4] = 'o';
    input[5] = ' ';
    input[6] = 'w';
    input[7] = 'o';
    input[8] = 'r';
    input[9] = 'l';
    input[10] = 'd';
    input[11] = '\0';
}