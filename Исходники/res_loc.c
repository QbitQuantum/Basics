/*
 * Converts a zone file representation in a string to an RDATA
 * on-the-wire representation.
 */
int loc_aton (const char *ascii, u_char *binary)
{
  char *cp, *maxcp;
  BYTE *bcp;
  DWORD latit     = 0, longit  = 0, alt = 0;
  DWORD lltemp1   = 0, lltemp2 = 0;
  int   altmeters = 0;
  int   altfrac   = 0;
  int   altsign   = 1;
  BYTE  hp        = 0x16;   /* default = 1e6 cm = 10000.00m = 10km */
  BYTE  vp        = 0x13;   /* default = 1e3 cm = 10.00m           */
  BYTE  siz       = 0x12;   /* default = 1e2 cm = 1.00m            */
  int   which1    = 0;
  int   which2    = 0;

  cp    = (char*)ascii;
  maxcp = cp + strlen (ascii);

  lltemp1 = latlon2ul (&cp, &which1);
  lltemp2 = latlon2ul (&cp, &which2);

  switch (which1 + which2)
  {
    case 3:                 /* 1 + 2, the only valid combination */
         if (which1 == 1 && which2 == 2)  /* normal case */
         {
           latit  = lltemp1;
           longit = lltemp2;
         }
         else if (which1 == 2 && which2 == 1) /* reversed */
         {
           longit = lltemp1;
           latit  = lltemp2;
         }
         else               /* some kind of brokenness */
           return (0);
         break;
    default:                /* we didn't get one of each */
         return (0);
  }

  /* altitude */
  if (*cp == '-')
  {
    altsign = -1;
    cp++;
  }

  if (*cp == '+')
     ++cp;

  while (isdigit(*cp))
     altmeters = altmeters * 10 + (*cp++ - '0');

  if (*cp == '.')                /* decimal meters */
  {
    cp++;
    if (isdigit(*cp))
    {
      altfrac = (*cp++ - '0') * 10;
      if (isdigit(*cp))
         altfrac += (*cp++ - '0');
    }
  }

  alt = (10000000 + (altsign * (altmeters * 100 + altfrac)));

  while (!isspace(*cp) && (cp < maxcp))
     cp++;                /* if trailing garbage or m */

  while (isspace(*cp) && (cp < maxcp))
     cp++;

  if (cp >= maxcp)
     goto defaults;

  siz = precsize_aton (&cp);

  while (!isspace(*cp) && (cp < maxcp)) /* if trailing garbage or m */
     cp++;

  while (isspace(*cp) && (cp < maxcp))
     cp++;

  if (cp >= maxcp)
     goto defaults;

  hp = precsize_aton (&cp);

  while (!isspace(*cp) && (cp < maxcp)) /* if trailing garbage or m */
     cp++;

  while (isspace(*cp) && (cp < maxcp))
     cp++;

  if (cp >= maxcp)
     goto defaults;

  vp = precsize_aton(&cp);

 defaults:

  bcp = binary;
  *bcp++ = (BYTE) 0;  /* version byte */
  *bcp++ = siz;
  *bcp++ = hp;
  *bcp++ = vp;
  PUTLONG (latit,bcp);
  PUTLONG (longit,bcp);
  PUTLONG (alt,bcp);

  return (16);            /* size of RR in octets */
}