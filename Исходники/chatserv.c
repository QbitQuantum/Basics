int chat_setroom( int unum, char *msg )
{
  char *modestr = nextword(&msg);
  int rnum = users[unum].room;
  int sign = 1;
  int flag;
  char *fstr;
  if (!OPERATOR(unum)) {
    send_to_unum(unum, "*** You're not operator\n", -1);
    return 0;
  }
  if (*modestr == '+') modestr++;
  else if (*modestr == '-') {
    modestr++;
    sign = 0;
  }
  if (*modestr == '\0') {
    send_to_unum(unum, "*** No flags specified\n", -1);
    return 0;
  }
  while (*modestr) {
    flag = 0;
    switch (*modestr) {
    case 'l': case 'L':
      flag = ROOM_LOCKED;
      fstr = "Locked";
      break;
    case 's': case 'S':
      flag = ROOM_SECRET;
      fstr = "Secret";
      break;
    default:
      sprintf(genbuf, "*** Unknown flag '%c'\n", *modestr);
      send_to_unum(unum, genbuf, -1);
    }
    if (flag && ((rooms[rnum].flags & flag) != sign*flag)) {
      rooms[rnum].flags ^= flag;
      sprintf(genbuf, "*** Mode change by %s to%s%s\n",
              users[unum].chatid, sign ? " " : " NOT ", fstr);
      send_to_room(rnum, genbuf, -1);
    }
    modestr++;
  }  
  return 0;  
}  