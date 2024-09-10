int main()
{
    unsigned x;
    int p, n;

    p = 8, n = 3;
    printf("Input a x: ");
    scanf("%x", &x);
    printf("After invert: %#x\n", invert(x, p, n));

    return 0;
}