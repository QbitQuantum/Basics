// char *gcvt(double number, size_t ndigits, char *buf);
int main() {
    char ptr[20];
    double a = 100;
    gcvt(a, 10, ptr);
    int length = strlen(ptr);
    printf("%s length = %d\n", ptr, length);
    return 0;
}