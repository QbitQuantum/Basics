static int
is_wlower_token(int c)
{ if (iswlower(c))
    return 1;
  if (c < 256 && islower(latin1_diacritics[c]))
    return 1;
  return 0;
}