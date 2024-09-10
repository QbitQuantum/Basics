void Timed::send_next_bootup_event(int value)
{
#if HAVE_DSME
  QDBusConnection dsme = QDBusConnection::systemBus() ;
  QString path = Maemo::Timed::objpath() ;
  QString iface = Maemo::Timed::interface() ;
  QString signal = "next_bootup_event" ;
  QDBusMessage m = QDBusMessage::createSignal(path, iface, signal) ;
  m << value ;
  if(dsme.send(m))
    log_info("signal %s(%d) sent", string_q_to_std(signal).c_str(), value) ;
  else
    log_error("Failed to send the signal %s(%d) on system bus: %s", string_q_to_std(signal).c_str(), value, dsme.lastError().message().toStdString().c_str()) ;
#endif
}