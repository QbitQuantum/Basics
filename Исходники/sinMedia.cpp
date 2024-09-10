void SINMOVIE::RenderStreamToSurfaceAll()
{
while (1)
{
  if (KeyState(VK_RETURN)) {  MovieState=2; ShutDown(); return; } 
  if (pSample->Update(0, NULL, NULL, 0) != S_OK) {  MovieState=2; ShutDown(); return; } 
  pMovieSurface->Blt(&DRect, pSurface, &SRect, DDBLT_WAIT, NULL); 
}
}