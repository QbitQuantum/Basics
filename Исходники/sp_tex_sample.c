/**
 * Apply texture coord wrapping mode and return integer texture indexes
 * for a vector of four texcoords (S or T or P).
 * \param wrapMode  PIPE_TEX_WRAP_x
 * \param s  the incoming texcoords
 * \param size  the texture image size
 * \param icoord  returns the integer texcoords
 * \return  integer texture index
 */
static INLINE void
nearest_texcoord_4(unsigned wrapMode, const float s[4], unsigned size,
                   int icoord[4])
{
   uint ch;
   switch (wrapMode) {
   case PIPE_TEX_WRAP_REPEAT:
      /* s limited to [0,1) */
      /* i limited to [0,size-1] */
      for (ch = 0; ch < 4; ch++) {
         int i = util_ifloor(s[ch] * size);
         icoord[ch] = REMAINDER(i, size);
      }
      return;
   case PIPE_TEX_WRAP_CLAMP:
      /* s limited to [0,1] */
      /* i limited to [0,size-1] */
      for (ch = 0; ch < 4; ch++) {
         if (s[ch] <= 0.0F)
            icoord[ch] = 0;
         else if (s[ch] >= 1.0F)
            icoord[ch] = size - 1;
         else
            icoord[ch] = util_ifloor(s[ch] * size);
      }
      return;
   case PIPE_TEX_WRAP_CLAMP_TO_EDGE:
      {
         /* s limited to [min,max] */
         /* i limited to [0, size-1] */
         const float min = 1.0F / (2.0F * size);
         const float max = 1.0F - min;
         for (ch = 0; ch < 4; ch++) {
            if (s[ch] < min)
               icoord[ch] = 0;
            else if (s[ch] > max)
               icoord[ch] = size - 1;
            else
               icoord[ch] = util_ifloor(s[ch] * size);
         }
      }
      return;
   case PIPE_TEX_WRAP_CLAMP_TO_BORDER:
      {
         /* s limited to [min,max] */
         /* i limited to [-1, size] */
         const float min = -1.0F / (2.0F * size);
         const float max = 1.0F - min;
         for (ch = 0; ch < 4; ch++) {
            if (s[ch] <= min)
               icoord[ch] = -1;
            else if (s[ch] >= max)
               icoord[ch] = size;
            else
               icoord[ch] = util_ifloor(s[ch] * size);
         }
      }
      return;
   case PIPE_TEX_WRAP_MIRROR_REPEAT:
      {
         const float min = 1.0F / (2.0F * size);
         const float max = 1.0F - min;
         for (ch = 0; ch < 4; ch++) {
            const int flr = util_ifloor(s[ch]);
            float u;
            if (flr & 1)
               u = 1.0F - (s[ch] - (float) flr);
            else
               u = s[ch] - (float) flr;
            if (u < min)
               icoord[ch] = 0;
            else if (u > max)
               icoord[ch] = size - 1;
            else
               icoord[ch] = util_ifloor(u * size);
         }
      }
      return;
   case PIPE_TEX_WRAP_MIRROR_CLAMP:
      for (ch = 0; ch < 4; ch++) {
         /* s limited to [0,1] */
         /* i limited to [0,size-1] */
         const float u = fabsf(s[ch]);
         if (u <= 0.0F)
            icoord[ch] = 0;
         else if (u >= 1.0F)
            icoord[ch] = size - 1;
         else
            icoord[ch] = util_ifloor(u * size);
      }
      return;
   case PIPE_TEX_WRAP_MIRROR_CLAMP_TO_EDGE:
      {
         /* s limited to [min,max] */
         /* i limited to [0, size-1] */
         const float min = 1.0F / (2.0F * size);
         const float max = 1.0F - min;
         for (ch = 0; ch < 4; ch++) {
            const float u = fabsf(s[ch]);
            if (u < min)
               icoord[ch] = 0;
            else if (u > max)
               icoord[ch] = size - 1;
            else
               icoord[ch] = util_ifloor(u * size);
         }
      }
      return;
   case PIPE_TEX_WRAP_MIRROR_CLAMP_TO_BORDER:
      {
         /* s limited to [min,max] */
         /* i limited to [0, size-1] */
         const float min = -1.0F / (2.0F * size);
         const float max = 1.0F - min;
         for (ch = 0; ch < 4; ch++) {
            const float u = fabsf(s[ch]);
            if (u < min)
               icoord[ch] = -1;
            else if (u > max)
               icoord[ch] = size;
            else
               icoord[ch] = util_ifloor(u * size);
         }
      }
      return;
   default:
      assert(0);
   }
}