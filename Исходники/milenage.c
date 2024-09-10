void f5star(u8* keyArr, u8* sqn_ak) {
    u8* out5;
    out5 = malloc(16);

    for (i = 0; i < 16; i++) {
        out5[i] = temp[i] ^ opc[i];
    }
    
    convertToBin(out5, binArr);
    rotWord(binArr, 128, 0x08);
    convertToHex(binArr, out5);

    for (i = 0; i < 16; i++) {
        out5[i] ^= c5[i];
    }
    encrypt(out5, keyArr, out5);

    for (i = 0; i < 16; i++) {
        out5[i] ^= opc[i];
    }

    printf("\r\nAK (f5*): ");
    for (i = 0; i < 6; i++) {
        ak[i] = out5[i];
        printf("%02x", ak[i]);
    }
    
    for (i = 0; i < 6; i++) {
        sqn[i] = ak[i] ^ sqn_ak[i];
    }
    
    u8 ind = (sqn[5] & 0b00011111);
    u8 seq = (sqn[5] & 0b11100000);
    ind = (ind + 1) % 32;
    sqn[5] = 0;
    sqn[5] |= ind;
    
    seq += 0b00100000;
    if (seq == 0) {
        sqn[4] += 1;
    }
    sqn[5] |= seq;
}