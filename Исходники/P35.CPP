void main ()  {
	int i;

	for (i=0; i < 4; i++)
		strset (a[i],'Z');
	for (i=0; i < 4; i++)
		PR (a[i]);
	getch();
}