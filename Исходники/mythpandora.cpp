void MythPianoService::BroadcastMessage(const char *format, ...)
{
  QString buffer;
  va_list args;
  va_start(args, format);
  buffer.vsprintf(format, args);
  va_end(args);

  //  printf("**** MythPianoService: %s\n", buffer.ascii());

  if (m_Listener)
    m_Listener->RecvMessage(buffer.ascii());
}