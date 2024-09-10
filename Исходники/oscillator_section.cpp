void OscillatorSection::paintBackground(Graphics& g) {
  static const float extra_knob_padding = 4.0f;
  static const DropShadow component_shadow(Colour(0x99000000), 3, Point<int>(0, 1));

  SynthSection::paintBackground(g);

  g.setColour(Colour(0xff212121));
  g.fillEllipse(transpose_1_->getBounds().toFloat().expanded(extra_knob_padding));
  g.fillEllipse(tune_1_->getBounds().toFloat().expanded(extra_knob_padding));
  g.fillEllipse(transpose_2_->getBounds().toFloat().expanded(extra_knob_padding));
  g.fillEllipse(tune_2_->getBounds().toFloat().expanded(extra_knob_padding));

  g.setColour(Colour(0xff303030));
  g.fillRect(0, tune_1_->getBottom() + 2, getWidth(), 5);

  g.setColour(Colour(0xff4fc3f7));
  g.strokePath(top_left_cross_path_, PathStrokeType(1.0f));

  g.setColour(Colour(0xff4fc3f7));
  g.strokePath(top_right_cross_path_, PathStrokeType(1.0f));

  g.setColour(Colour(0xff4fc3f7));
  g.strokePath(bottom_left_cross_path_, PathStrokeType(1.0f));

  g.setColour(Colour(0xff4fc3f7));
  g.strokePath(bottom_right_cross_path_, PathStrokeType(1.0f));

  g.setColour(Colour(0xffbbbbbb));
  g.setFont(Fonts::getInstance()->proportional_regular().withPointHeight(10.0f));
  drawTextForComponent(g, TRANS("MOD"), cross_modulation_);
  drawTextForComponent(g, TRANS("TRANS"), transpose_1_);
  drawTextForComponent(g, TRANS("TRANS"), transpose_2_);
  drawTextForComponent(g, TRANS("TUNE"), tune_1_);
  drawTextForComponent(g, TRANS("TUNE"), tune_2_);
  drawTextForComponent(g, TRANS("UNISON"), unison_detune_1_);
  drawTextForComponent(g, TRANS("UNISON"), unison_detune_2_);

  component_shadow.drawForRectangle(g, wave_viewer_1_->getBounds());
  component_shadow.drawForRectangle(g, wave_viewer_2_->getBounds());

  g.setColour(Colour(0xff424242));
  paintKnobShadows(g);
}