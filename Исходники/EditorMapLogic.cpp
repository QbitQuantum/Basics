//---------------------------------------------------------------------------------------------
void TEditorMapLogic::CheckTerrainGroupUpdateForSave()
{
  Ogre::TerrainGroup* pTG = GetC()->pGraphicEngine->GetGE()->GetTerrainGroup();
  // проверка: идёт ли создание данных для теней и света для земли
  if( pTG->isDerivedDataUpdateInProgress() )
  {
    if( flgIsTerrainGroupUpdate == false )
    {
      // начался процесс создания, TODO: вывести сообщение в GUI?
      flgIsTerrainGroupUpdate = true;
    }
  }
  else
  {
    if( flgIsTerrainGroupUpdate )
    {
      // закончился процесс создания, TODO: вывести сообщение в GUI?
      pTG->saveAllTerrains( false );
      flgIsTerrainGroupUpdate = false;
    }
  }
  // README: флаг flgIsTerrainGroupUpdate надо учитывать при попытке загрузки карты.
}