void
select_palette (struct frame *f, HDC hdc)
{
  struct w32_display_info *display_info = FRAME_DISPLAY_INFO (f);

  if (!display_info->has_palette)
    return;

  if (display_info->palette == 0)
    return;

  if (!NILP (Vw32_enable_palette))
    f->output_data.w32->old_palette =
      SelectPalette (hdc, display_info->palette, FALSE);
  else
    f->output_data.w32->old_palette = NULL;

  if (RealizePalette (hdc) != GDI_ERROR)
  {
    Lisp_Object frame, framelist;
    FOR_EACH_FRAME (framelist, frame)
    {
      SET_FRAME_GARBAGED (XFRAME (frame));
    }