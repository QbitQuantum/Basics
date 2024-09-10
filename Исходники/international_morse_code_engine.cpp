void
MorseCodeDecoderNode::add(QString code, QChar character, int level)
{
  if (level == code.size()) {
    if (m_character == QChar('\0') && character.isLower())
      m_character = character;
  } else {
    QChar part = code[level];
    MorseCodeDecoderNode * branch;
    if (part == '.') {
      if (!m_dot_branch)
	m_dot_branch = new MorseCodeDecoderNode();
      branch = m_dot_branch;
    }
    else {
      if (!m_dash_branch)
	m_dash_branch = new MorseCodeDecoderNode();
      branch = m_dash_branch;
    }
    branch->add(code, character, level+1);
  }
}