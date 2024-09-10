void main() {	/*  0 = defecto: 1 = a:  2 = b: 3 = c: */
	char *q,a[100];
	int i;

	i = getdisk();
	if (getcurdir (0,a) == -1) {   		/* Por defecto */
		q = _strerror ("Error en getcur dir()");
		PRS(q);
		getch(); exit(1);
	}
	printf ("Directorio actual en %c: = %s\n",i + 'a',a);


	/* Determina el directorio actual en a: */


	if (getcurdir (1,a) == -1) {   		/* Unidad a: */
		q = _strerror ("Error en getcur dir()");
		PRS(q);
		getch(); exit(1);
	}
	printf ("Directorio actual en a: = %s\n",a);
	getch();

}