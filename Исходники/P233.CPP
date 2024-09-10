void main() {
    char *p,*a,q[100];

    strcpy (q,"link.exe");
    p = searchpath (q);   /* El valor de q no cambia */
    if (p == NULL) {
        a = _strerror ("Error en searchpath ()");
        PRS(a);
        getch();
        exit (1);
    }
    PRS(p);
    SALTO;
    getch();
}