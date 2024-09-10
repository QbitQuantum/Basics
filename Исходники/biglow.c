void main(void)
{   int Hdl;
    void *OldScreen;
    int dummy;
    long i;

/* d‚termine la base line A pour la position souris
*/
    linea_init();

/* charge l'image et la duplique en largeur
*/       
    Hdl=Fopen("MORETA.NEO",0); if (Hdl<0) { appl_exit(); Pterm0(); }
    Fseek(4L,Hdl,0);
    Fread(Hdl,32L,NewPalette);
    Fseek(128L,Hdl,0);
    for (i=0;i<200;i++) 
    {    LINE1 *p=(LINE1 *)&picbuf[0].line[i];
         Fread(Hdl,sizeof(LINE1),p);
         p[1]=p[0];
    }
    Fclose(Hdl);

/* Duplique l'image en hauteur 
*/  
    picbuf[1]=picbuf[0];
         
/* Installe la pallette et sauve l'ancienne
*/
    InsPalette(); 
    
/* Sauve l'adresse de l'‚cran courant
*/  
    OldScreen=GetScreenPtr();

/* Installe la routine de scrolling en VBL
*/
    InsVBL(Scrolling);
    
/* Boucle en attendant un Ctrl-C
*/
    while (1) if (Bconstat(2)<0 && (char)Bconin(2)==3) break;

/* Remet tout en ordre et sort de l…
*/  
    RmvVBL();
    SetScreenPtr(OldScreen);
    SetScroll(0);
    SetLineStride(0);
    RestPalette();
}