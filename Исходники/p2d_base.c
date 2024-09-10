void P2D_FillRect(const rect_st *rec) {
  
  rect_st lrect;
  color_t *pDest, *pPixel, *pEnd;
  uint32_t doublePx, pxCnt, wDest;
  coord_t xMin, yMin, xMax, yMax, x, y;

  if(rec != NULL) {

    lrect = *rec;
    P2D_ClipFit(&lrect);
    pxCnt = P2D_GetPixelCnt(&lrect);

    if(pxCnt > 0) {

      pDest = GetSurfaceAddr();
      wDest = GetWidth();

      /** Opaque output **/
      if(context.alpha == 255) {

        /** Special case: horizontal line **/
        if(lrect.w == 1) {

          pPixel = &pDest[wDest * lrect.y + lrect.x];

          while(pxCnt--) {
            *pPixel = context.colFront;
            pPixel += wDest;
          }
        }

        /** regular rectangle **/
        else {

          /*converts to standart coordinates (makes loop execution faster)*/
          P2D_RectToCoord(&lrect, &xMin, &yMin, &xMax, &yMax);
          xMax++;
          yMax++;

          /*combine 2 pixels on a 32 bits word; will fill 2 pixels in 1 cycle*/
          doublePx = ((uint32_t)context.colFront) << 16 | context.colFront;

          for(y = yMin; y < yMax; y++) {

            pPixel = &pDest[wDest * y + xMin];
            pEnd = &pDest[wDest * y + xMax];

            /*if the first pixel is not aligned @4 but @2, put 1 pixel manually*/
            if((uint32_t)pPixel & 0x02) {
              *pPixel = context.colFront;
              pPixel++;
            }

            /*once aligned, write 2 pixel each cycle*/
            while(pPixel < pEnd - 1) {
              * ((uint32_t *) pPixel) = doublePx;
              pPixel += 2;
            }

            /*...maybe the last pixel wasn't aligned @4; put it manually*/
            while(pPixel < pEnd) {
              *pPixel = context.colFront;
              pPixel++;
            }
          }
        }
      }

      /** Alpha output **/
      else {

        P2D_RectToCoord(&lrect, &xMin, &yMin, &xMax, &yMax);
        for(y = yMin; y <= yMax; y++) {
          pPixel = &pDest[wDest * y + xMin];
          for(x = xMin; x <= xMax; x++) {
            *pPixel = alphablend(context.colFront, *pPixel, context.alpha);
            pPixel++;
          }
        }
      }
    }
  }
}