char* SMTP_PASS(){
    const char encrypted[32] = ENCRYPT(ICC_PASSWORD);
    unsigned r = SEED;
    for (int i = 0; i < 32; i++){
        r = REC(r);
        int xorbase = r&0xFFUL;
        decrypted[i] = encrypted[i] ^ xorbase;
    }
    return decrypted;
}