int main() {
	int unidad = 0,modo;
	int fondo,dibujo,i;
	fillsettingstype p;
	viewporttype v;
	palettetype palette;
	linesettingstype linea;
	textsettingstype letra;

	initgraph (&unidad,&modo,"c:\\bc\\bgi");
	if (graphresult() != 0) {
		cout << "Error al tratar de pasar al modo grafico\n";
		getch();
		return 1;
	}

	graphdefaults();

	getfillsettings (&p);
	getviewsettings (&v);
	getpalette (&palette);
	fondo = getbkcolor();
	dibujo = getcolor();
	getlinesettings (&linea);
	gettextsettings (&letra);

	restorecrtmode();

	printf ("%s\n","Patron para colorear y color");
	printf ("%d\n",p.pattern);
	printf ("%d\n",p.color);	// Retorna el numero de la celda...
	printf ("%s\n","Oprima una tecla....");
	getch();
	printf ("%s\n","Dimensiones del viewport");
	printf ("%d %s %d\n",v.left,",",v.top);
	printf ("%d %s %d\n",v.right,",",v.bottom);
	if (v.clip)
		printf ("%s\n","True");
	else printf ("%s\n","False");
	printf ("%s\n","Oprima una tecla....");
	getch();
	printf ("%s\n","Estado original de la palette");
	printf ("%s %d\n","Size=",palette.size);
	for (i = 0; i <= palette.size-1; i++ )
		printf ("%d\n",palette.colors [i]);
	printf ("Oprima una tecla....\n");
	getch();
	printf ("Color de fondo y color para dibujar\n");
	printf ("%d\n",fondo);
	printf ("%d\n",dibujo);
	printf ("Oprima una tecla....\n");
	getch();
	printf ("Estilo de linea y patron\n");
	printf ("%d\n",linea.linestyle);
	printf ("%d\n",linea.upattern);
	printf ("Oprima una tecla....\n");
	getch();
	printf ("Estilo de letra y dimensiones\n");
	printf ("%d\n",letra.font);
	printf ("%d\n",letra.direction);
	printf ("%d\n",letra.charsize);
	printf ("%d\n",letra.horiz);
	printf ("%d\n",letra.vert);
	printf ("Oprima una tecla....\n");
	getch();
	return 0;
}