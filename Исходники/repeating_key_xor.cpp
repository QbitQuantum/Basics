int main(int argc, char **argv)
{
    if (argc > 1) {
        char Message[MAXLEN];
        FILE *infile = fopen(argv[1], "r");
        Stopif(infile == 0, "Couldn't open file %s", argv[1]);
        uint32 MessageLength = fread(Message, sizeof(char),
                                     MAXLEN, infile);
        uint32 HexMessageLength = 2*MessageLength;
        char HexMessage[HexMessageLength + 1];
        StringToHex(HexMessage, Message, MessageLength);

        char ResultCipher[HexMessageLength + 1];
        EncryptMessage(ResultCipher, HexMessage, HexMessageLength);
        printf("%s\n", ResultCipher);
        fclose(infile);
    }
}