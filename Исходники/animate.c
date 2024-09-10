Bool AnimateObject(object_node *obj, int dt)
{
   Bool need_redraw = False;
   list_type over_list;

   if (OF_FLICKERING == (OF_FLICKERING & obj->flags))
   {
      obj->lightAdjust = rand() % FLICKER_LEVEL;
      need_redraw = TRUE;
   }

   if (OF_FLASHING == (OF_FLASHING & obj->flags))
   {
      DWORD angleFlash;
      obj->bounceTime += min(dt,50);
      if (obj->bounceTime > TIME_FLASH)
         obj->bounceTime -= TIME_FLASH;
      angleFlash = NUMDEGREES * obj->bounceTime / TIME_FLASH;
      obj->lightAdjust = FIXED_TO_INT(fpMul(FLASH_LEVEL, SIN(angleFlash)));
      need_redraw = TRUE;
   }

   if (obj->animate->animation != ANIMATE_NONE)
   {
      object_bitmap_type obj_bmap;
      obj_bmap = FindObjectBitmap(obj->icon_res);
      if (obj_bmap != NULL)
    need_redraw |= AnimateSingle(obj->animate, BitmapsNumGroups(obj_bmap->bmaps), dt);
   }
   
   if (OF_PHASING == (OF_PHASING & obj->flags))
   {
      int anglePhase;
      obj->phaseTime += min(dt,40);
      if (obj->phaseTime > TIME_FULL_OBJECT_PHASE)
         obj->phaseTime -= TIME_FULL_OBJECT_PHASE;
      anglePhase = numPhases * obj->phaseTime / TIME_FULL_OBJECT_PHASE;
      obj->drawingtype = phaseStates[anglePhase];
      need_redraw = TRUE;
   }
   // Animate object's overlays
   for (over_list = *(obj->overlays); over_list != NULL; over_list = over_list->next)
   {
      object_bitmap_type obj_bmap;
      Overlay *overlay = (Overlay *) (over_list->data);
      if (overlay->animate.animation == ANIMATE_NONE)
    continue;

      obj_bmap = FindObjectBitmap(overlay->icon_res);
      if (obj_bmap != NULL)
      {
    need_redraw |= AnimateSingle(&overlay->animate, BitmapsNumGroups(obj_bmap->bmaps), dt);
      }      
   }
   return need_redraw;
}