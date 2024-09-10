int main() {
	char cxt[512] = {0};
	byte key[] = "hello, worldxxyy";
	byte pt[] = "this is the plaintext";
	byte ct[32] = {0};
	byte pt2[32] = {0};

	aes.set_key(cxt, key, 16);
	encrypt(cxt, pt, sizeof(pt), ct);
	printf("cipher text:\n");
	hexdump(ct, 32);

	decrypt(cxt, ct, 32, pt2);
	printf("decrypted text:\n");
	hexdump(pt2, 32);
	printf("%s\n", pt2);

	return 0;
}