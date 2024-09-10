void WaveViewer::paint(juce::Graphics &g) {
  g.drawImageWithin(background_,
                    0, 0, getWidth(), getHeight(), RectanglePlacement());

  if (wave_phase_) {
    if (phase_ >= 0.0 && phase_ < 1.0) {
      float x = phaseToX(phase_);
      g.setColour(Colour(0x33ffffff));
      g.fillRect(x - 0.5f, 0.0f, 1.0f, (float)getHeight());

      float y = PADDING + (getHeight() - 2 * PADDING) * (1.0f - amp_) / 2.0f;

      if (is_control_rate_)
        g.setColour(Colour(0xff00e676));
      else
        g.setColour(Colour(0xff03a9f4));
      g.fillEllipse(x - MARKER_WIDTH / 2.0f, y - MARKER_WIDTH / 2.0f,
                    MARKER_WIDTH, MARKER_WIDTH);
      g.setColour(Colour(0xff000000));
      g.fillEllipse(x - MARKER_WIDTH / 4.0f, y - MARKER_WIDTH / 4.0f,
                    MARKER_WIDTH / 2.0f, MARKER_WIDTH / 2.0f);
    }
  }
}