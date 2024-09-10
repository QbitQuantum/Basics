void main(int argc, char *argv[], char *env[]) {
	int i;
	char *p;

	i = execlpe ("c:\\bc\\work1\\prog.exe",argv[0],"llave",argv[2],NULL,env);
	if (i == -1) {
		p = _strerror ("Error en execlpe");
		printf ("%s\n%d\n",p,argc);
		getch(); exit(1);
	}
	getch();
}