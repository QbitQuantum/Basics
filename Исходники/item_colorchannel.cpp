void
ItemColorChannel::process_action(const MenuAction& action)
{
  switch (action)
  {
    case MenuAction::REMOVE:
      remove_char();
      break;

    case MenuAction::LEFT:
      *m_number = truncf(*m_number * 10.0f) / 10.0f;
      *m_number -= 0.1f;
      *m_number = math::clamp(*m_number, 0.0f, 1.0f);
      set_text(float_to_string(*m_number));
      break;


    case MenuAction::RIGHT:
      *m_number = truncf(*m_number * 10.0f) / 10.0f;
      *m_number += 0.1f;
      *m_number = math::clamp(*m_number, 0.0f, 1.0f);
      set_text(float_to_string(*m_number));
      break;

    default:
      break;
  }
}