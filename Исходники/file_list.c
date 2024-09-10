static inline u16 __toupper(u16 c)
{
  if (ISLOWER(c))
  {
    c -= 0x0061/*'a'*/ - 0x0041/*'A'*/;
  }
  else if (IS_CHINESE(c))
  {
    iconv_t hiconv = iconv_open("euccn", "ucs2le");
    if(hiconv != (iconv_t)-1)
    {
      char inbuf[2];
      char outbuf[2];
      char *p_inbuf = inbuf;
      char *p_outbuf = outbuf;
      size_t src_len = 2;
      size_t dest_len =  2;
      u16 gb2312_code = 0;

      inbuf[0] = (u8)c;
      inbuf[1] = (u8)(c >> 8);
      iconv(hiconv, &p_inbuf, &src_len, &p_outbuf, &dest_len);
      iconv_close(hiconv);

      gb2312_code = MAKE_WORD2(outbuf[0], outbuf[1]);
      c = __get_first_py_letter(gb2312_code);
    }
  }