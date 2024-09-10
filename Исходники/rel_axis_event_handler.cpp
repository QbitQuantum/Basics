void
RelAxisEventHandler::update(int msec_delta)
{
  if (m_repeat == -1 && m_stick_value != 0.0f)
  {
    // new and improved REL style event sending

    float rel_value = m_stick_value * m_value * static_cast<float>(msec_delta) / 1000.0f;

    // keep track of the rest that we lose when converting to integer
    rel_value += m_rest_value;
    m_rest_value = rel_value - truncf(rel_value);

    m_rel_emitter->send(static_cast<int>(rel_value));
  }
}