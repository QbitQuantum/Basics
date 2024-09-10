Inform& Inform::operator<<(unsigned long u) {
  char tmpbuf[128];
  sprintf(tmpbuf, "%ld", u);
  strncat(buf, tmpbuf, MAX_MSG_SIZE - strlen(buf));
  return *this;
}