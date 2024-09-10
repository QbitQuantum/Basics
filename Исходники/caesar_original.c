int main (int argc, char *argv[]){
	//int c = sizeof("one");
	int a = isUpper('a');
	int b = isLower('a');
	int c = isUpper('Z');
	int d = isLower('Z');
	char r = shiftChar('.', 1);
	printf("%d %d %d %d\n", a,b,c,d);
	printf("%c\n", r);
	
	char *message = strdup("M! K fobi pkcd, iod kd dswoc pbecdbkdsxq vkxqekqo.");
	printf("message    : %s\n", message);
	encryptInPlace(message,-10);
	printf("ciphertext : %s\n\n", message);
	
	char *message1 = strdup("M! K fobi pkcd, iod kd dswoc pbecdbkdsxq vkxqekqo.");
	printf("message    : %s\n", message1);
	char *ciphertext = encrpytNewMemory(message1,-10);
	printf("ciphertext : %s\n", ciphertext);
	free(ciphertext);
	printf("ciphertext : %s\n", ciphertext);
	test();
	return 0;
}