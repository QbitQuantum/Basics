void main() {
	int id;
	char *p;

	if ( (id = _creat ("prueba",FA_ARCH) ) == -1) {
		p = _strerror ("Error _creat()");
		PRS (p);
		getch(); exit(1);
	}
	if ( _close (id) == -1) {
		p = strerror (errno);
		PRS (p);
		getch();
		exit(1);
	}
	getch();
}