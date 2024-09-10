void pix_movement :: threshMessCallback(void *data, t_floatarg newmode)
{
  GetMyClass(data)->threshold=CLAMP((float)255.*newmode);
}