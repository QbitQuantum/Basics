void main() {
	int Comparacion (const void *p, const void *q);
	char aux[10];
	int n,*p;
	unsigned int Num = sizeof (a) / sizeof (int);
	cout << "De numero a buscar" << endl;
	gets (aux);
	n = atoi (aux);
	while ( n != 9999 ) {
		p =  (int *) lfind (	(void *) &n, // Direccion de la llave
										(void *)a,  // Arreglo
										&Num,		  // Numero de elementos
										sizeof (int), 	// Longitud de cada
															// elemento
										Comparacion
							);
		if (p != NULL) {
				cout << "Si existe, ";
				printf ("en la posicion = %d\n",p-q);
		}
		else {
						cout << "No existe. " << endl;

		}
		cout << "De numero a buscar. 9999 para terminar " << endl;
		gets (aux);
		n = atoi (aux);
	}
}