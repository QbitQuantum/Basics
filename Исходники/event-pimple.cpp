static void remove_cred_modifier(QVector<Maemo::Timed::cred_modifier_io_t> &x, const QString &token, bool accrue)
{
  Maemo::Timed::cred_modifier_io_t lookFor ;
  lookFor.token = token ;
  lookFor.accrue = accrue ;
  for(int i = x.indexOf(lookFor); i != -1; i = x.indexOf(lookFor))
  {
    x.remove(i) ;
  }
}