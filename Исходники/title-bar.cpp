void TitleBar::OnDraw(const Context &context) {
  using namespace base;
  using namespace graphic;

  int scale = context.surface()->GetScale();

  const RectF bounds = GetBounds() * scale;
  float factor = 0.5f * scale;

  Paint paint;
  paint.SetAntiAlias(true);
  paint.SetStyle(Paint::kStyleFill);

  Point2F points[2] = {{factor, bounds.top + factor}, {factor, bounds.bottom}};
  uint32_t colors[2] = {0xFFE7E7E7, 0xFFD7D7D7};
  float pos[2] = {0.f, 1.f};

  Shader shader = GradientShader::MakeLinear(points, colors, pos, 2, Shader::kTileModeClamp);
  paint.SetShader(shader);

  context.canvas()->DrawRect(RectF::FromLTRB(bounds.left + factor,
                                             bounds.top + factor,
                                             bounds.right - factor,
                                             bounds.bottom), paint);

  paint.Reset();
  paint.SetAntiAlias(true);
  paint.SetStyle(Paint::kStyleFill);
  paint.SetFont(font_);
  paint.SetTextSize(font_.GetSize() * scale);

  paint.SetColor(Theme::GetData().title_bar.active.foreground.colors[0]);

  float text_width = paint.MeasureText(title_.c_str(), title_.length());

  SkTextBox text_box;
  // Put the foreground at the center
  text_box.setBox(bounds.l + (bounds.width() - text_width) / 2.f,
                  bounds.t + 1.f, // move down a little for better look
                  bounds.r - (bounds.width() - text_width) / 2.f,
                  bounds.b);
  text_box.setSpacingAlign(SkTextBox::kCenter_SpacingAlign);
  text_box.setText(title_.c_str(), title_.length(), paint.GetSkPaint());
  text_box.draw(context.canvas()->GetSkCanvas());

}