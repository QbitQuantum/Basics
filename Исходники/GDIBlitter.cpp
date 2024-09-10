JNIEXPORT void JNICALL Java_org_apache_harmony_awt_gl_windows_GDIBlitter_bltBGImage
  (JNIEnv *env, jobject obj, jint srcX, jint srcY, jlong srcSurfStruct, jobject srcData, 
  jint dstX, jint dstY, jlong dstSurfStruct, jint width, jint height, 
  jint bgcolor, jint compType, jfloat alpha, jdoubleArray matrix, jintArray clip, 
  jint numVertex, jboolean invalidated, jintArray dirtyRegions, jint regCount){

      SURFACE_STRUCTURE *srcSurf = (SURFACE_STRUCTURE *)srcSurfStruct;
      SURFACE_STRUCTURE *dstSurf = (SURFACE_STRUCTURE *)dstSurfStruct;

      srcSurf->invalidated = invalidated != 0;
      HDC tmpDC = CreateCompatibleDC(dstSurf->gi->hdc);
      int w = srcSurf->width;
      int h = srcSurf->height;
      HBITMAP tmpBmp = CreateCompatibleBitmap(dstSurf->gi->hdc, w, h);
      SelectObject(tmpDC, tmpBmp);

      BYTE a = (BYTE)((bgcolor >> 24) & 0xff);
      BYTE r = (BYTE)((bgcolor >> 16) & 0xff);
      BYTE g = (BYTE)((bgcolor >> 8) & 0xff);
      BYTE b = (BYTE)(bgcolor & 0xff);
      r = MUL(a, r);
      g = MUL(a, g);
      b = MUL(a, b);

      HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
      SelectObject(tmpDC, brush);
      PatBlt(tmpDC, 0, 0, w, h, PATCOPY);
      
      int *regions;
      if(dirtyRegions == 0){
          regCount = 4;
          regions = (int *)malloc(4 * sizeof(int));
          regions[0] = 0;
          regions[1] = 0;
          regions[2] = srcSurf->width - 1;
          regions[3] = srcSurf->height - 1;
      } else {
          regions = (int *)malloc(regCount * sizeof(int));
          env->GetIntArrayRegion(dirtyRegions, 1, regCount, regions);
      }

      if(initBitmap(srcSurf, env, srcData, true, regions, regCount)){
          BLENDFUNCTION bf;
          bf.AlphaFormat = AC_SRC_ALPHA;
          bf.BlendOp = AC_SRC_OVER;
          bf.BlendFlags = 0;
          bf.SourceConstantAlpha = 255;
          AlphaBlend(tmpDC, 0, 0, w, h, srcSurf->srcDC, 0, 0, w, h, bf);
      }

      UCHAR srca = (UCHAR)(alpha * 255 + 0.5);

      XFORM currentTransform, transform;
      if(matrix != NULL){

          jdouble * mtrx = (jdouble *)env->GetPrimitiveArrayCritical(matrix, 0);
          jdouble * old_mtrx = mtrx;

          transform.eM11 = (FLOAT)(*mtrx++);
          transform.eM12 = (FLOAT)(*mtrx++);
          transform.eM21 = (FLOAT)(*mtrx++);
          transform.eM22 = (FLOAT)(*mtrx++);
          transform.eDx = (FLOAT)(*mtrx++);
          transform.eDy = (FLOAT)(*mtrx);

          env->ReleasePrimitiveArrayCritical(matrix, old_mtrx, 0);

          SetGraphicsMode(dstSurf->gi->hdc, GM_ADVANCED);
          GetWorldTransform(dstSurf->gi->hdc, &currentTransform);
          SetWorldTransform(dstSurf->gi->hdc, &transform);
      }

      HRGN oldClip = setGdiClip(env, dstSurf->gi->hdc, clip, numVertex);

      BLITSTRUCT blitStruct;
      memset(&blitStruct, 0, sizeof(BLITSTRUCT));

      switch(compType){
          case COMPOSITE_CLEAR:
          case COMPOSITE_SRC_OUT:
              blitStruct.blitFunctintType = BIT_BLT;
              blitStruct.rastOp = BLACKNESS;
              break;

          case COMPOSITE_SRC:
          case COMPOSITE_SRC_IN:
              blitStruct.blitFunctintType = BIT_BLT;
              if(srca == 0) blitStruct.rastOp = BLACKNESS;
              else blitStruct.rastOp = SRCCOPY;
              break;

          case COMPOSITE_DST:
          case COMPOSITE_DST_OVER:
              return;

          case COMPOSITE_SRC_ATOP:
          case COMPOSITE_SRC_OVER:
              if(srca == 255){
                  blitStruct.blitFunctintType = BIT_BLT;
                  blitStruct.rastOp = SRCCOPY;
              }else{

                  blitStruct.blitFunctintType = ALPHA_BLEND;
                  blitStruct.blendFunc.AlphaFormat = 0;
                  blitStruct.blendFunc.BlendOp = AC_SRC_OVER;
                  blitStruct.blendFunc.BlendFlags = 0;
                  blitStruct.blendFunc.SourceConstantAlpha = srca;
              }
              break;

          case COMPOSITE_DST_IN:
          case COMPOSITE_DST_ATOP:
              if(srca != 0) return;
              blitStruct.blitFunctintType = BIT_BLT;
              blitStruct.rastOp = BLACKNESS;
              break;

          case COMPOSITE_DST_OUT:
          case COMPOSITE_XOR:
              if(srca != 255) return;
              blitStruct.blitFunctintType = BIT_BLT;
              blitStruct.rastOp = BLACKNESS;
              break;
      }

      switch(blitStruct.blitFunctintType){
          case ALPHA_BLEND:
              AlphaBlend(dstSurf->gi->hdc, dstX, dstY, width, height, tmpDC,
                      srcX, srcY, width, height, blitStruct.blendFunc);
              break;

          case TRANSPARENT_BLT:
              TransparentBlt(dstSurf->gi->hdc, dstX, dstY, width, height, tmpDC,
                  srcX, srcY, width, height, srcSurf->rtc);
              break;

          default:
              BitBlt(dstSurf->gi->hdc, dstX, dstY, width, height, tmpDC,
                  srcX, srcY, blitStruct.rastOp);
              break;
      }
      if(matrix){
          SetWorldTransform(dstSurf->gi->hdc, &currentTransform);
          SetGraphicsMode(dstSurf->gi->hdc, GM_COMPATIBLE);
      }
      restoreGdiClip(dstSurf->gi->hdc, oldClip);

      DeleteObject(brush);
      DeleteObject(tmpBmp);
      DeleteDC(tmpDC);

  }