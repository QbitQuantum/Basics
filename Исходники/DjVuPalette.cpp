int
DjVuPalette::compute_palette(int maxcolors, int minboxsize)
{
  if (!hist)
    G_THROW( ERR_MSG("DjVuPalette.no_color") );
  if (maxcolors<1 || maxcolors>MAXPALETTESIZE)
    G_THROW( ERR_MSG("DjVuPalette.many_colors") );
  
  // Paul Heckbert: "Color Image Quantization for Frame Buffer Display", 
  // SIGGRAPH '82 Proceedings, page 297.  (also in ppmquant)
  
  // Collect histogram colors
  int sum = 0;
  int ncolors = 0;
  GTArray<PData> pdata;
  { // extra nesting for windows
    for (GPosition p = *hist; p; ++p)
    {
      pdata.touch(ncolors);
      PData &data = pdata[ncolors++];
      int k = hist->key(p);
      data.p[0] = (k>>16) & 0xff;
      data.p[1] = (k>>8) & 0xff;
      data.p[2] = (k) & 0xff;
      data.w = (*hist)[p];
      sum += data.w;
    }
  }
  // Create first box
  GList<PBox> boxes;
  PBox newbox;
  newbox.data = pdata;
  newbox.colors = ncolors;
  newbox.boxsize = 256;
  newbox.sum = sum;
  boxes.append(newbox);
  // Repeat spliting boxes
  while (boxes.size() < maxcolors)
    {
      // Find suitable box
      GPosition p;
      for (p=boxes; p; ++p)
        if (boxes[p].colors>=2 && boxes[p].boxsize>minboxsize) 
          break;
      if (! p)
        break;
      // Find box boundaries
      PBox &splitbox = boxes[p];
      unsigned char pmax[3];
      unsigned char pmin[3];
      pmax[0] = pmin[0] = splitbox.data->p[0];
      pmax[1] = pmin[1] = splitbox.data->p[1];
      pmax[2] = pmin[2] = splitbox.data->p[2];
      { // extra nesting for windows
        for (int j=1; j<splitbox.colors; j++)
        {
          pmax[0] = umax(pmax[0], splitbox.data[j].p[0]);
          pmax[1] = umax(pmax[1], splitbox.data[j].p[1]);
          pmax[2] = umax(pmax[2], splitbox.data[j].p[2]);
          pmin[0] = umin(pmin[0], splitbox.data[j].p[0]);
          pmin[1] = umin(pmin[1], splitbox.data[j].p[1]);
          pmin[2] = umin(pmin[2], splitbox.data[j].p[2]);
        }
      }
      // Determine split direction and sort
      int bl = pmax[0]-pmin[0]; 
      int gl = pmax[1]-pmin[1];
      int rl = pmax[2]-pmin[2];
      splitbox.boxsize = (bl>gl ? (rl>bl ? rl : bl) : (rl>gl ? rl : gl));
      if (splitbox.boxsize <= minboxsize)
        continue;
      if (gl == splitbox.boxsize)
        qsort(splitbox.data, splitbox.colors, sizeof(PData), gcomp);
      else if (rl == splitbox.boxsize)
        qsort(splitbox.data, splitbox.colors, sizeof(PData), rcomp);
      else
        qsort(splitbox.data, splitbox.colors, sizeof(PData), bcomp);
      // Find median
      int lowercolors = 0;
      int lowersum = 0;
      while (lowercolors<splitbox.colors-1 && lowersum+lowersum<splitbox.sum)
        lowersum += splitbox.data[lowercolors++].w;
      // Compute new boxes
      newbox.data = splitbox.data + lowercolors;
      newbox.colors = splitbox.colors - lowercolors;
      newbox.sum = splitbox.sum - lowersum;
      splitbox.colors = lowercolors;
      splitbox.sum = lowersum;
      // Insert boxes at proper location
      GPosition q;
      for (q=p; q; ++q)
        if (boxes[q].sum < newbox.sum)
          break;
      boxes.insert_before(q, newbox);
      for (q=p; q; ++q)
        if (boxes[q].sum < splitbox.sum)
          break;
      boxes.insert_before(q, boxes, p);
    }
  // Fill palette array
  ncolors = 0;
  palette.empty();
  palette.resize(0,boxes.size()-1);
  { // extra nesting for windows
    for (GPosition p=boxes; p; ++p)
    {
      PBox &box = boxes[p];
      // Compute box representative color
      float bsum = 0;
      float gsum = 0;
      float rsum = 0;
      for (int j=0; j<box.colors; j++)
        {
          float w = (float)box.data[j].w;
          bsum += box.data[j].p[0] * w;
          gsum += box.data[j].p[1] * w;
          rsum += box.data[j].p[2] * w;
        }
      PColor &color = palette[ncolors++];
      color.p[0] = (unsigned char) fmin(255, bsum/box.sum);
      color.p[1] = (unsigned char) fmin(255, gsum/box.sum);
      color.p[2] = (unsigned char) fmin(255, rsum/box.sum);
      color.p[3] = ( color.p[0]*BMUL + color.p[1]*GMUL + color.p[2]*RMUL) / SMUL;
    }
  }
  // Save dominant color
  PColor dcolor = palette[0];
  // Sort palette colors in luminance order
  qsort((PColor*)palette, ncolors, sizeof(PColor), lcomp);
  // Clear invalid data
  colordata.empty();
  delete pmap;
  pmap = 0;
  // Return dominant color
  return color_to_index_slow(dcolor.p);
}