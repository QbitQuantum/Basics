static void
OnAirspacePaintListItem(Canvas &canvas, const PixelRect rc, unsigned i)
{
  assert(i < AIRSPACECLASSCOUNT);

  const AirspaceComputerSettings &computer =
    CommonInterface::SettingsComputer().airspace;
  const AirspaceRendererSettings &renderer =
    CommonInterface::SettingsMap().airspace;

  int w1, w2, x0;
  int w0 = rc.right - rc.left - Layout::FastScale(4);

  w1 = canvas.text_width(_("Warn")) + Layout::FastScale(10);
  w2 = canvas.text_width(_("Display")) + Layout::FastScale(10);
  x0 = w0 - w1 - w2;

  if (colormode) {
    canvas.white_pen();
#ifdef ENABLE_SDL
    canvas.select(Graphics::solid_airspace_brushes[renderer.colours[i]]);
#else
#ifdef HAVE_ALPHA_BLEND
    if (renderer.transparency && AlphaBlendAvailable()) {
      canvas.select(Graphics::solid_airspace_brushes[renderer.colours[i]]);
    } else {
#endif
      canvas.set_text_color(Graphics::GetAirspaceColourByClass(i, renderer));
      canvas.set_background_color(Color(0xFF, 0xFF, 0xFF));
      canvas.select(Graphics::GetAirspaceBrushByClass(i, renderer));
#ifdef HAVE_ALPHA_BLEND
    }
#endif
#endif
    canvas.rectangle(rc.left + x0, rc.top + Layout::FastScale(2),
        rc.right - Layout::FastScale(2), rc.bottom - Layout::FastScale(2));
  } else {
    if (computer.warnings.class_warnings[i])
      canvas.text(rc.left + w0 - w1 - w2, rc.top + Layout::FastScale(2),
                  _("Warn"));

    if (renderer.display[i])
      canvas.text(rc.left + w0 - w2, rc.top + Layout::FastScale(2),
                  _("Display"));
  }

  canvas.text_clipped(rc.left + Layout::FastScale(2),
      rc.top + Layout::FastScale(2), x0 - Layout::FastScale(10),
                      airspace_class_as_text((AirspaceClass_t)i, false));
}