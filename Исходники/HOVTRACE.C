int FollowTrace (fixed tracex, fixed tracey, long deltax, long deltay, int max)
{
  int tx,ty,otx,oty;
  long absdx,absdy,xstep,ystep;

  tx = tracex>>TILESHIFT;
  ty = tracey>>TILESHIFT;

  absdx=LABS(deltax);
  absdy=LABS(deltay);

  if (absdx>absdy)
  {
    ystep = (deltay<<8)/(absdx>>8);

    if (!ystep)
      ystep = deltay>0 ? 1 : -1;

    oty = (tracey+ystep)>>TILESHIFT;
    if (deltax>0)
    {
//###############
//
// step x by +1
//
//###############
      do
      {
	tx++;
	tracey+=ystep;
	ty = tracey>>TILESHIFT;

	if (ty!=oty)
	{
	  if (tilemap[tx-1][ty])
	  {
	    tile.x = tx-1;
	    tile.y = ty;
	    return 1;
	  }
	  oty = ty;
	}
	if (tilemap[tx][ty])
	{
	  tile.x = tx;
	  tile.y = ty;
	  return 1;
	}
      } while (--max);
      return 0;
    }
    else
    {
//###############
//
// step x by -1
//
//###############
      do
      {