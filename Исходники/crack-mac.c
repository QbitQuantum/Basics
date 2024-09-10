char upcase(char ch){
	if(islower(ch))
		ch -= 'a' - 'A';
	return ch;
}