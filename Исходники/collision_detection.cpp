void
close_sdl(void)
{
	printf("close_sdl()\n");

	/* free loaded image */
	gDotTexture.free();


	/* destroy window */
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;


	/* Quit SDL subsystem */
#ifdef _SDL_TTF_H
	TTF_Quit();
#endif
	IMG_Quit();
	SDL_Quit();
}