SDL_Surface* Diff(SDL_Surface* entry, SDL_Surface* moy)
{
  for(int i = 0; i < entry->w; i++)
  {
    for(int j = 0; j < entry->h; j ++)
    {
      //rajouter surement boucle for
      defPixel(entry, i, j, getpixel(entry, i, j) - getpixel(moy, i, j));
    }
  }
  return entry;
}