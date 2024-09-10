AppletParameter::AppletParameter(const char *name, const char *value)
: m_isValid(false), m_formattedString(NULL)
{
  _ASSERT(name != NULL);
  _ASSERT(value != NULL);

  m_isValid = isStringValid(name) && isStringValid(value);

  if (isValid()) {
    const char *format = "<PARAM NAME=\"%s\" VALUE=\"%s\" >\n";

    int len = _scprintf(format, name, value) + 1;

    m_formattedString = new char[len];

    sprintf_s(m_formattedString, (size_t)(len), format, name, value);
  }
}