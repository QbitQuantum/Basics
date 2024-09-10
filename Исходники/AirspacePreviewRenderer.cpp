bool
AirspacePreviewRenderer::PrepareFill(
    Canvas &canvas, AirspaceClass type, const AirspaceLook &look,
    const AirspaceRendererSettings &settings)
{
  const AirspaceClassRendererSettings &class_settings = settings.classes[type];

  if (class_settings.fill_mode ==
      AirspaceClassRendererSettings::FillMode::NONE)
    return false;

#ifdef ENABLE_OPENGL
  ::glEnable(GL_BLEND);
  ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Color color = class_settings.fill_color;
  canvas.Select(Brush(color.WithAlpha(48)));
#elif defined(ENABLE_SDL)
  Color color = class_settings.fill_color;
  canvas.Select(Brush(LightColor(color)));
#else
  canvas.Select(look.brushes[settings.transparency ?
                             3 : class_settings.brush]);
  canvas.SetTextColor(LightColor(class_settings.fill_color));
  canvas.SetMixMask();
#endif

  canvas.SelectNullPen();

  return true;
}