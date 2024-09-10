int WebRequest::contentLength() const
{
  std::string lenstr = envValue("CONTENT_LENGTH");

  if (lenstr.empty())
    return 0;
  else
    return atoi(lenstr.c_str());
}