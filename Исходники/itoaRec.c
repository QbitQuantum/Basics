int main(void) {
    Itoa(123456789, BUFFER, BUFFER_SIZE);
    printf("%s\n", BUFFER);

    Itoa(0, BUFFER, 256);
    printf("%s\n", BUFFER);

    getchar();
    return 0;
}