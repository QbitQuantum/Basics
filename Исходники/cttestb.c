void exit(int value)
{
    exit_value = value;
    longjmp(exit_jmp, 1);
}