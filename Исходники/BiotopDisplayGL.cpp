void CBiotopDisplayGL::DrawAllVisibleEntities(bool noStep)
{
  int cbx_min, cby_min, cbx_max, cby_max;
  GetVisibleBiotopCoord(cbx_min, cby_min, cbx_max, cby_max);
  int i;
  CAnimatedSprite* pAnimatedSprite = NULL;
  bool isSelected = false;
  int inst = 0;
  int curAction = 0;

  m_tSpriteDisplayPrio.RemoveAll();

  for (i=0; i<m_pBiotop->getNbOfEntities(); i++) 
  {
    int posMapX,posMapY,coordx,coordy,offsetx,offsety;
    CBasicEntity* pEntity = m_pBiotop->getEntityByIndex(i); 

    if ( (pEntity == NULL) || (pEntity->isToBeRemoved()) )
      continue;
 
    Point_t coord = pEntity->getStepCoord();

    if ( (coord.x>=cbx_min)&&(coord.x<=cbx_max)
       &&(coord.y>=cby_min)&&(coord.y<=cby_max) )
    {
      // Process coordonate
      ConvertCoordBiotopStepToMapStep(coord.x,coord.y,posMapX,posMapY);
      m_Map.GetAbsCoordFromBlockStepPos(posMapX,posMapY,coordx,coordy,offsetx,offsety);
 
      DisplayPriority_t element;
      element.pEntity         = pEntity;
      element.displayPriority = ((pEntity->getLayer())<<16) - coordy;
      element.newMapCoordX    = coordx;
      element.newMapCoordY    = coordy;      
      element.spriteOffsetX   = offsetx;
      element.spriteOffsetY   = offsety;

      // Insert the item in proper position according to displayPriority
      INT_PTR start = 0, end = m_tSpriteDisplayPrio.GetSize(); 
      while(start < end) 
      { 
          INT_PTR pos = (start + end) / 2; 
          if(element.displayPriority > m_tSpriteDisplayPrio.GetAt(pos).displayPriority) 
              start = pos + 1; 
          else 
              end = pos; 
      } 
      m_tSpriteDisplayPrio.InsertAt(start, element); 
    }
    else
    {
      // Force step attribute for next move
      pAnimatedSprite = GetAnimatedSprite(pEntity);
      if (pAnimatedSprite != NULL)
      {
        inst = pAnimatedSprite->GetInstance(pEntity->getId(), pEntity->getColorRgb(), pEntity->getWeight());
        // Force NO step attribute for next move
        pAnimatedSprite->SetStepMode(inst,true);
      }
    }
  }

  m_RefreshCounter = (m_RefreshCounter+1)%m_nbRefreshPerStep;

  for (i=0; i<m_tSpriteDisplayPrio.GetSize(); i++) 
  {
    int coordx,coordy,offsetx,offsety;

    DisplayPriority_t element = m_tSpriteDisplayPrio.GetAt(i);
    CBasicEntity* pEntity = element.pEntity; 
    coordx  = element.newMapCoordX;
    coordy  = element.newMapCoordY;
    offsetx = element.spriteOffsetX;
    offsety = element.spriteOffsetY;

    // Check if selected entity
    isSelected = (pEntity->getId() == m_nSelectedEntityId);

    pAnimatedSprite = GetAnimatedSprite(pEntity);

    if (pAnimatedSprite == NULL)
      break;

    inst = pAnimatedSprite->GetInstance(pEntity->getId(), pEntity->getColorRgb(), pEntity->getWeight());

    if (noStep)
      pAnimatedSprite->MoveSprite(inst,coordx,coordy);
    else if ( m_RefreshCounter == 0)
      pAnimatedSprite->MoveSpriteByStep(inst,coordx,coordy);

    if (pEntity->getBrain() != NULL)
    {
      curAction = pEntity->getBrain()->GetCurrentReactionIndex();
      // According to speed, use walk or run animation instead of real action
      /*if ( pEntity->getCurrentSpeed() > 20)
        curAction = pAnimatedSprite->m_idActionRun;   
      else if ( pEntity->getCurrentSpeed() > 0)
        curAction = pAnimatedSprite->m_idActionWalk;*/
    }
    else
      curAction = 0;

    if (isSelected)
    {
      int posMapX,posMapY,coordx,coordy,offsetx,offsety;
      Point_t coord = pEntity->getGridCoord();
      ConvertCoordBiotopGridToMap(coord.x,coord.y,posMapX,posMapY);
      m_Map.GetAbsCoordFromBlockStepPos((posMapX)*NB_STEPS_PER_GRID_SQUARE+(1+(posMapY&1))*NB_STEPS_PER_GRID_SQUARE/2,(posMapY+1)*NB_STEPS_PER_GRID_SQUARE,coordx,coordy,offsetx,offsety);
      m_SprSquare.MoveSpriteAtPosition(coordx+offsetx,coordy+offsety);
      m_SprSquare.DrawSprite(m_appBindTexArray[SQUARE_ID]);
    }

    if (pEntity->getClass()>=CLASS_ANIMAL_FIRST)
      pAnimatedSprite->DrawSprite(inst,offsetx,offsety,pEntity->getDirection(),0,curAction,isSelected);
    else
      pAnimatedSprite->DrawSprite(inst,offsetx,offsety,0,0,curAction,isSelected);

    // Force step attribute for next move
    if ( m_RefreshCounter == 0)
      pAnimatedSprite->SetStepMode(inst,false);
  }

}