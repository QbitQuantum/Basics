void main() {
	char c;

	PRS("De caracteres...<R> para terminar.");
	while ( (c=getch()) != 13) 	/* La funcion getch(), no hace eco */
		fputchar (c);           /* Escribe c en el video */
}