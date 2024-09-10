/* GeglOperationPointFilter gives us a linear buffer to operate on
 * in our requested pixel format
 */
static gboolean
process (GeglOperation       *op,
         void                *in_buf,
         void                *out_buf,
         glong                n_pixels,
         const GeglRectangle *roi,
         gint                 level)
{
  GeglProperties *o = GEGL_PROPERTIES (op);
  gfloat     *in_pixel;
  gfloat     *out_pixel;
  gfloat      black_level = (gfloat) o->black_level;
  gfloat      diff;
  gfloat      exposure_negated = (gfloat) -o->exposure;
  gfloat      gain;
  gfloat      white;
  
  glong       i;

  in_pixel = in_buf;
  out_pixel = out_buf;
  
  white = exp2f (exposure_negated);
  diff = MAX (white - black_level, 0.01);
  gain = 1.0f / diff;

  for (i=0; i<n_pixels; i++)
    {
      out_pixel[0] = (in_pixel[0] - black_level) * gain;
      out_pixel[1] = (in_pixel[1] - black_level) * gain;
      out_pixel[2] = (in_pixel[2] - black_level) * gain;
      out_pixel[3] = in_pixel[3];
      
      out_pixel += 4;
      in_pixel  += 4;
    }
    
  return TRUE;
}