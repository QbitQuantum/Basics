void sh_poke(char* params){
	// poke pointer byte(decimal)
	int i;
	for(i=0;i<strLen(params);i++){
		if(params[i] == ' ') break;
	}
	char substr[i+1];
	memCopy(params,substr,i);
	substr[i] = 0;
	char* pointer = (char*) ((int*)strToInt(substr));
	
	char substr2[strLen(params)-i];
	memCopy(params+i+1,substr2,strLen(params)-i);
	int value = strToInt(substr2);
	*pointer = value;
}