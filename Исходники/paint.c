BOOL APIENTRY
IntEngPaint(IN SURFOBJ *pso,
            IN CLIPOBJ *ClipRegion,
            IN BRUSHOBJ *Brush,
            IN POINTL *BrushOrigin,
            IN MIX  Mix)
{
  SURFACE *psurf = CONTAINING_RECORD(pso, SURFACE, SurfObj);
  BOOL ret;

  DPRINT("pso->iType == %u\n", pso->iType);
  /* Is the surface's Paint function hooked? */
  if((pso->iType!=STYPE_BITMAP) && (psurf->flags & HOOK_PAINT))
  {
    // Call the driver's DrvPaint
    ret = GDIDEVFUNCS(pso).Paint(
      pso, ClipRegion, Brush, BrushOrigin, Mix);
    return ret;
  }
  return EngPaint(pso, ClipRegion, Brush, BrushOrigin, Mix );

}