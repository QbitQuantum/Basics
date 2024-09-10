static PetscErrorCode PetscDrawResizeWindow_Win32(PetscDraw draw,int w,int h)
{
  PetscDraw_Win32 *windraw = (PetscDraw_Win32*)draw->data;
  RECT            r;

  PetscFunctionBegin;
  GetWindowRect(windraw->hWnd,&r);
  MoveWindow(windraw->hWnd,r.left,r.top,(int)w,(int)h,TRUE);
  /* set all variable dealing with window dimensions */
  windraw->node->bitheight = windraw->h = draw->h = h;
  windraw->node->bitwidth  = windraw->w = draw->w = w;
  /* set up graphic buffers with the new size of window */
  SetBitmapDimensionEx(windraw->node->BufferBit,w,h,NULL);
  if (windraw->node->DoubleBuffered) SetBitmapDimensionEx(windraw->node->DoubleBufferBit,w,h,NULL);
  windraw->haveresized = PETSC_TRUE;
  PetscFunctionReturn(0);
}