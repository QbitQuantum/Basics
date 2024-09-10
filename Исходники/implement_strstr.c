int main() {

    char *a = "hello world";
    char *b = "llo";
    printf("%s, %s, %d\n", a, b, strStr(a, b));
    return 0;
}