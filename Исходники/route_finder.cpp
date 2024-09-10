int is_route_possible(int fromx, int fromy, int tox, int toy, Bitmap *wss)
{
  wallscreen = wss;
  suggestx = -1;

  // ensure it's a memory bitmap, so we can use direct access to line[] array
  if ((wss == NULL) || (!wss->IsMemoryBitmap()) || (wss->GetColorDepth() != 8))
    quit("is_route_possible: invalid walkable areas bitmap supplied");

  if (wallscreen->GetPixel(fromx, fromy) < 1)
    return 0;

  Bitmap *tempw = BitmapHelper::CreateBitmapCopy(wallscreen, 8);

  if (tempw == NULL)
    quit("no memory for route calculation");
  if (!tempw->IsMemoryBitmap())
    quit("tempw is not memory bitmap");

  int dd, ff;
  // initialize array for finding widths of walkable areas
  int thisar, inarow = 0, lastarea = 0;
  int walk_area_times[MAX_WALK_AREAS + 1];
  for (dd = 0; dd <= MAX_WALK_AREAS; dd++) {
    walk_area_times[dd] = 0;
    walk_area_granularity[dd] = 0;
  }

  for (ff = 0; ff < tempw->GetHeight(); ff++) {
    const uint8_t *tempw_scanline = tempw->GetScanLine(ff);
    for (dd = 0; dd < tempw->GetWidth(); dd++) {
      thisar = tempw_scanline[dd];
      // count how high the area is at this point
      if ((thisar == lastarea) && (thisar > 0))
        inarow++;
      else if (lastarea > MAX_WALK_AREAS)
        quit("!Calculate_Route: invalid colours in walkable area mask");
      else if (lastarea != 0) {
        walk_area_granularity[lastarea] += inarow;
        walk_area_times[lastarea]++;
        inarow = 0;
      }
      lastarea = thisar;
    }
  }

  for (dd = 0; dd < tempw->GetWidth(); dd++) {
    for (ff = 0; ff < tempw->GetHeight(); ff++) {
      uint8_t *tempw_scanline = tempw->GetScanLineForWriting(ff);
      thisar = tempw_scanline[dd];
      if (thisar > 0)
        tempw_scanline[dd] = 1;
      // count how high the area is at this point
      if ((thisar == lastarea) && (thisar > 0))
        inarow++;
      else if (lastarea != 0) {
        walk_area_granularity[lastarea] += inarow;
        walk_area_times[lastarea]++;
        inarow = 0;
      }
      lastarea = thisar;
    }
  }

  // find the average "width" of a path in this walkable area
  for (dd = 1; dd <= MAX_WALK_AREAS; dd++) {
    if (walk_area_times[dd] == 0) {
      walk_area_granularity[dd] = MAX_GRANULARITY;
      continue;
    }

    walk_area_granularity[dd] /= walk_area_times[dd];
    if (walk_area_granularity[dd] <= 4)
      walk_area_granularity[dd] = 2;
    else if (walk_area_granularity[dd] <= 15)
      walk_area_granularity[dd] = 3;
    else
      walk_area_granularity[dd] = MAX_GRANULARITY;

    /*char toprnt[200];
       sprintf(toprnt,"area %d: Gran %d", dd, walk_area_granularity[dd]);
       winalert(toprnt); */
  }
  walk_area_granularity[0] = MAX_GRANULARITY;

  tempw->FloodFill(fromx, fromy, 232);
  if (tempw->GetPixel(tox, toy) != 232) 
  {
    // Destination pixel is not walkable
    // Try the 100x100 square around the target first at 3-pixel granularity
    int tryFirstX = tox - 50, tryToX = tox + 50;
    int tryFirstY = toy - 50, tryToY = toy + 50;

    if (!find_nearest_walkable_area(tempw, tryFirstX, tryFirstY, tryToX, tryToY, tox, toy, 3))
    {
      // Nothing found, sweep the whole room at 5 pixel granularity
      find_nearest_walkable_area(tempw, 0, 0, tempw->GetWidth(), tempw->GetHeight(), tox, toy, 5);
    }

    delete tempw;
    return 0;
  }
  delete tempw;

  return 1;
}