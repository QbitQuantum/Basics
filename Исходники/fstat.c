int strls_unix(PCStr(path),PVStr(ls),int size){
	FILE *tmp = TMPFILE("CRYPT-ls");
	const char *tail;

	ls_unix(tmp,"-l",VStrNULL,path,NULL);
	fflush(tmp);
	fseek(tmp,0,0);
	fgets(ls,size,tmp);
	fclose(tmp);
	if( tail = strpbrk(ls,"\r\n") ){
		*(char*)tail = 0;
	}
	return 0;
}