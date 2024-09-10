void des3_encrypt_blk(unsigned char *blk, int len) {

    DWORD dlen;
    dlen = len;

    if(CryptEncrypt(hDESKey[0][0], 0, FALSE, 0, blk, &dlen, len + 8) == 0)
	fatalbox("Error encrypting block!\n");
    if(CryptDecrypt(hDESKey[0][1], 0, FALSE, 0, blk, &dlen) == 0)
	fatalbox("Error encrypting block!\n");
    if(CryptEncrypt(hDESKey[0][2], 0, FALSE, 0, blk, &dlen, len + 8) == 0)
	fatalbox("Error encrypting block!\n");
}