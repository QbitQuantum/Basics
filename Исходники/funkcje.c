void rysuj_pilke(BITMAP * bufor, int x_pilka, int y_pilka)
{
	circle(bufor, x_pilka, y_pilka, rozmiar_pilka, makecol(255,64,64));
	circlefill(bufor, x_pilka, y_pilka, rozmiar_pilka-5, makecol(255,112,41));
	floodfill(bufor, x_pilka, y_pilka+rozmiar_pilka-1, makecol(255,230,102));
}