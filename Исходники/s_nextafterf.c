int main(int argc, char **argv)
{
        int cnt, i;
        float a, b;
        cnt = atoi(argv[1]);
        a = strtod(argv[2], NULL);
        b = strtod(argv[3], NULL);
        while (cnt-- > 0) {
                for (i = 0; i < sizeof(a); i++) {
                        unsigned char c = ((char*)(&a))[i];
                        printf("%x%x", (c >> 4), (c & 0xf));
                }
                printf(" %f\n", a);
                a = nextafterf(a, b);
        }
        return 0;
}