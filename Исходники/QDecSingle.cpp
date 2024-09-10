double QDecSingle::toDouble() const
{
  char str[MaxStrSize] = {0};
  decSingleToString(&m_data, str);
  return strtod(str, 0);
}