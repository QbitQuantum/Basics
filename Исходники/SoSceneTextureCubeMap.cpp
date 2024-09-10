SoCamera *
SoSceneTextureCubeMapP::findCamera(void)
{
  SoSearchAction sa;

  sa.setType(SoCamera::getClassTypeId());
  sa.setInterest(SoSearchAction::FIRST);
  sa.apply(PUBLIC(this)->scene.getValue());

  SoPath * path = sa.getPath();

  if (path == NULL)
    return NULL;
  else
    return (SoCamera *)path->getTail();
}