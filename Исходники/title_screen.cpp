void
TitleScreen::make_tux_jump()
{
  static bool jumpWasReleased = true;
  Sector& sector  = m_titlesession->get_current_sector();
  Player& tux = sector.get_player();

  m_controller->update();
  m_controller->press(Control::RIGHT);

  // Check if we should press the jump button
  Rectf lookahead = tux.get_bbox();
  lookahead.set_right(lookahead.get_right() + 96);
  bool pathBlocked = !sector.is_free_of_statics(lookahead);
  if ((pathBlocked && jumpWasReleased) || !tux.on_ground()) {
    m_controller->press(Control::JUMP);
    jumpWasReleased = false;
  } else {
    jumpWasReleased = true;
  }

  // Wrap around at the end of the level back to the beginning
  if (sector.get_width() - 320 < tux.get_pos().x) {
    sector.activate("main");
    sector.get_camera().reset(tux.get_pos());
  }
}