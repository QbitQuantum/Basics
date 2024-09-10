void main(int argc, char *argv[],char *env[]) {
	FILE *p;
	char a[30];
	int i = spawnve (P_WAIT,"prog.exe",argv,env);

	if (i == -1) {
		printf ("%s %s %d\n",strerror (errno),argv[0],argc );
		getch();
		exit (1);
	}
	p = fopen("prueba","r");
	fgets (a,100,p);
	while (!feof(p)) {
		printf ("%s",a);
		fgets (a,100,p);
	}
	fclose (p);
	getch();
}