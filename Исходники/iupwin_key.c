int iupwinKeyDecode(int wincode)
{
  HKL k;
  int i, count;

  k = GetKeyboardLayout(0);    
  if ((int)HIWORD(k) == 0x0416) /* ABNT */
  {
    int abnt_count = sizeof(keytable_abnt)/sizeof(keytable_abnt[0]);
    for (i = 0; i < abnt_count; i++)
    {
      if (keytable_abnt[i].wincode == wincode)
        return winKeyMap2Iup(keytable_abnt, i);
    }
  }

  count = sizeof(winkey_map)/sizeof(winkey_map[0]);
  for (i = 0; i < count; i++)
  {
    if (winkey_map[i].wincode == wincode)
      return winKeyMap2Iup(winkey_map, i);
  }

  return 0;
}