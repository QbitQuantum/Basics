GameMatrix* newGameMatrix(SDL_Surface *screen, int matrixHeight, int matrixWidth)
{
	int i = 0,j = 0;
	
	/** Crée la surface de jeu **/
	GameMatrix *surface = malloc(sizeof(GameMatrix));
	/// Dimensions de la grille de jeu
	surface->height = matrixHeight;
	surface->width = matrixWidth;
	surface->surf = createTable(surface->height, surface->width);
	
	// Calcul de la largeur d'un bloc en fonction des dimensions de la fenêtre
	surface->coteBloc = (HEIGHT-CADRE*2)/surface->height;
	
	// Initialisation de la surface à 0
	for(i = 0; i < surface->height; i++)
		for(j = 0; j < surface->width; j++)
			surface->surf[i][j] = 0;
				
	// Initialisation des couleurs		
	surface->colors[0] = SDL_MapRGB(screen->format, 255,0,0); // Rouge
	surface->colors[1] = SDL_MapRGB(screen->format, 0,0,255); // Bleu
	surface->colors[2] = SDL_MapRGB(screen->format, 189,141,70); // Brun
	surface->colors[3] = SDL_MapRGB(screen->format, 255,0,255); // Magenta
	surface->colors[4] = SDL_MapRGB(screen->format, 255,255,255); // Blanc
	surface->colors[5] = SDL_MapRGB(screen->format, 0,255,255); // Cyan
	surface->colors[6] = SDL_MapRGB(screen->format, 0,255,0); // Vert
	
	return surface;
}