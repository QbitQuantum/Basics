int main(int argc, string argv[])
{
    if (argc == 1) {
        printf("Usage: './vigenere' keyword\n");
        return 1;
    }
    else if (argc == 2) {
        if (check_wordkey(argv[1]) < 0) {
            printf("Wrong argument\n");
            return 1;
        }
        string encrypted_text = encrypt(argv[1]);
        printf("%s\n", encrypted_text);
    }
    else {
        printf("Wrong number of arguments\n");
        return 1;
    }
    return 0;
}