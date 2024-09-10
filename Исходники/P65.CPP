void main() {
	double x,leer_double();
	int n,signo,d,leer_entero();
	char *p;

	x = leer_double(); 		/* Lee un dato de tipo double */
					/* Ver funcion leer_double() */
	d = leer_entero();		/* Lee un dato de tipo entero */
					/* Ver funcion leer_entero() */
	p = ecvt (x,d,&n,&signo);
	printf ("%s %d %d\n",p,n,signo);
	getch();
}