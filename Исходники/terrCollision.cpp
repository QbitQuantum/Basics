bool TerrainBlock::castRayI(const Point3F &start, const Point3F &end, RayInfo *info, bool collideEmpty)
{
   lineCount = 0;
   lineStart = start;
   lineEnd = end;

   info->object = this;

   if(start.x == end.x && start.y == end.y)
   {
      if (end.z == start.z)
         return false;

      F32 height;
      if(!getNormalAndHeight(Point2F(start.x, start.y), &info->normal, &height, true))
         return false;
      F32 t = (height - start.z) / (end.z - start.z);
      if(t < 0 || t > 1)
         return false;
      info->t = t;
      return true;
   }

   F32 invBlockWorldSize = 1 / F32(mSquareSize * BlockSquareWidth);

   Point3F pStart(start.x * invBlockWorldSize, start.y * invBlockWorldSize, start.z);
   Point3F pEnd(end.x * invBlockWorldSize, end.y * invBlockWorldSize, end.z);

   int blockX = (S32)mFloor(pStart.x);
   int blockY = (S32)mFloor(pStart.y);

   int dx, dy;

   F32 invDeltaX;
   if(pEnd.x == pStart.x)
   {
      calcInterceptX = calcInterceptNone;
      invDeltaX = 0;
      dx = 0;
   }
   else
   {
      invDeltaX = 1 / (pEnd.x - pStart.x);
      calcInterceptX = calcInterceptV;
      if(pEnd.x < pStart.x)
         dx = -1;
      else
         dx = 1;
   }

   F32 invDeltaY;
   if(pEnd.y == pStart.y)
   {
      calcInterceptY = calcInterceptNone;
      invDeltaY = 0;
      dy = 0;
   }
   else
   {
      invDeltaY = 1 / (pEnd.y - pStart.y);
      calcInterceptY = calcInterceptV;
      if(pEnd.y < pStart.y)
         dy = -1;
      else
         dy = 1;
   }
   F32 startT = 0;
   for(;;)
   {
      F32 nextXInt = calcInterceptX(pStart.x, invDeltaX, (F32)(blockX + (dx == 1)));
      F32 nextYInt = calcInterceptY(pStart.y, invDeltaY, (F32)(blockY + (dy == 1)));

      F32 intersectT = 1;

      if(nextXInt < intersectT)
         intersectT = nextXInt;
      if(nextYInt < intersectT)
         intersectT = nextYInt;

      if(castRayBlock(pStart, pEnd, Point2I(blockX * BlockSquareWidth, blockY * BlockSquareWidth), BlockShift, invDeltaX, invDeltaY, startT, intersectT, info, collideEmpty)) {
         info->normal.z *= BlockSquareWidth * mSquareSize;
         info->normal.normalize();
         return true;
      }

      startT = intersectT;
      if(intersectT >= 1)
         break;
      if(nextXInt < nextYInt)
         blockX += dx;
      else if(nextYInt < nextXInt)
         blockY += dy;
      else
      {
         blockX += dx;
         blockY += dy;
      }
   }
   return false;
}