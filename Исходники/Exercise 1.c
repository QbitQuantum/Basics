//Places many characters
void putPhrase(char *string){
	int i;
	for(i = 0; i < 16; i++){
		putChar(string[i]);
	}
}