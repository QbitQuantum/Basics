int main()
{
  unsigned status;
  if ((status = _xbegin()) == _XBEGIN_STARTED) {
    _xend();
  } else {
    _xabort(_XABORT_CONFLICT);
  }
}