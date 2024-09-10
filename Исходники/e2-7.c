int main(void)
{
    int n = 7;
    int p = 16;
    unsigned x = ~0;

    printf("x before:       ");
    print_bits(x, sizeof(x));
    printf("x after invert: ");
    print_bits(invert(x, p, n), sizeof(x));

    return 0;
}