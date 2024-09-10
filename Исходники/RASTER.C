/*-----------------------------------------------------------------------

   tiga_blit_in_card

   Does an on-board BitBLT.

-----------------------------------------------------------------------*/
void tiga_blit_in_card(tigaRast *rSrc, Coor srcX, Coor srcY,
                       tigaRast *rDst, Coor dstX, Coor dstY,
                       Coor width, Coor height)
{
   /* Ignore multiple raster case for now, assume rSrc = rDst. */

   bitblt(width, height, srcX, srcY, dstX, dstY);

   return;
}