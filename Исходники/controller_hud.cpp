ControllerHUD::ControllerHUD() :
  m_controls()
{
  const Sizef btn_size(16, 16);
  const Vector pos(128, 64);

  const Vector dpad_pos = pos + Vector(-64.0f, 0.0f);
  m_controls[Control::LEFT] = Rectf::from_center(dpad_pos + Vector(-16.0f, 0.0f), btn_size);
  m_controls[Control::RIGHT] = Rectf::from_center(dpad_pos + Vector(16.0f, 0.0f), btn_size);
  m_controls[Control::UP] = Rectf::from_center(dpad_pos + Vector(0.0f, -16.0f), btn_size);
  m_controls[Control::DOWN] = Rectf::from_center(dpad_pos + Vector(0.0f, 16.0f), btn_size);

  const Vector peek_pos = pos + Vector(0.0f, -24.0f);
  m_controls[Control::PEEK_LEFT] = Rectf::from_center(peek_pos + Vector(-16.0f, 0.0f), btn_size);
  m_controls[Control::PEEK_RIGHT] = Rectf::from_center(peek_pos + Vector(16.0f, 0.0f), btn_size);
  m_controls[Control::PEEK_UP] = Rectf::from_center(peek_pos + Vector(0.0f, -16.0f), btn_size);
  m_controls[Control::PEEK_DOWN] = Rectf::from_center(peek_pos + Vector(0.0f, 16.0f), btn_size);

  const Vector btn_pos = pos + Vector(64.0f, -8.0f);
  m_controls[Control::ACTION] = Rectf::from_center(btn_pos + Vector(-20.0f, 0.0f), btn_size);
  m_controls[Control::JUMP] = Rectf::from_center(btn_pos + Vector(0.0f, 20.0f), btn_size);

  m_controls[Control::START] = Rectf::from_center(pos + Vector(16.0f, 24.0f), Sizef(16, 8));
  m_controls[Control::ESCAPE] = Rectf::from_center(pos + Vector(-16.0f, 24.0f), Sizef(16, 8));
}