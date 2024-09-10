Label *createImageLabel(SDL_Surface *image, int x, int y)
{
	Label *l;

	l = malloc(sizeof(Label));

	if (l == NULL)
	{
		showErrorAndExit("Failed to allocate %d bytes to create image Label", (int)sizeof(Label));
	}

	l->text = copyImage(image, 0, 0, image->w, image->h);

	l->x = x;

	l->y = y;

	return l;
}