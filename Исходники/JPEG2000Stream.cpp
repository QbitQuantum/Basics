void JPXStream::init()
{
  Object oLen;
  if (getDict()) getDict()->lookup("Length", &oLen);

  int bufSize = BUFFER_INCREASE;
  if (oLen.isInt()) bufSize = oLen.getInt();
  oLen.free();

  unsigned char *buf = (unsigned char*)gmallocn(bufSize, sizeof(unsigned char));
  int index = 0;

  str->reset();
  int c = str->getChar();
  while(c != EOF)
  {
    if (index >= bufSize)
    {
      bufSize += BUFFER_INCREASE;
      buf = (unsigned char*)greallocn(buf, bufSize, sizeof(unsigned char));
    }
    buf[index] = c;
    ++index;
    c = str->getChar();
  }

  init2(buf, index, CODEC_JP2);

  free(buf);

  counter = 0;
  inited = gTrue;
}