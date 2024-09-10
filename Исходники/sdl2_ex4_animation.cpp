//Cette fonction effectue une fermeture appropriée du programme, de l'environnement SDL et libère la mémoire des différents éléments SDL créés
void close()
{

  //On détruit les LTextures créées dans le programme
  hommeTexture.free();

  //Destroy window
  SDL_DestroyRenderer(rendererFenetre);
  SDL_DestroyWindow(fenetreProgramme);
  fenetreProgramme = NULL;
  rendererFenetre = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}