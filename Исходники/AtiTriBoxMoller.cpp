static inline bool8 AtiPlaneBoxOverlap( const TBM_FLOAT normal[3], const TBM_FLOAT d, const TBM_FLOAT maxbox[3])
{
   TBM_FLOAT vmin[3];
   TBM_FLOAT vmax[3];
   for (int32 q = X; q <= Z; q++)
   {
      if (normal[q] > TBM_ZERO)
      {
         vmin[q] = -maxbox[q];
         vmax[q] = maxbox[q];
      }
      else
      {
         vmin[q] = maxbox[q];
         vmax[q] = -maxbox[q];
      }
   }
   if (DOT (normal, vmin) + d > TBM_ZERO)
   {
      return FALSE;
   }
   if (DOT (normal, vmax) + d >= TBM_ZERO)
   {
      return TRUE;
   }
   return FALSE;
}