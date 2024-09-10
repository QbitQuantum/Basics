int
__loadctype(const char *name)
{
  FILE *fp;
  char id[sizeof(_CTYPE_ID) - 1];
  u_int32_t i, len;
  unsigned short *new_ctype = NULL;
  unsigned char *new_toupper = NULL, *new_tolower = NULL;

  _DIAGASSERT(name != NULL);

  if ((fp = fopen(name, "r")) == NULL)
    return 0;

  if (fread(id, sizeof(id), 1, fp) != 1)
    goto bad;

  if (memcmp(id, _CTYPE_ID, sizeof(id)) != 0)
    goto bad;

  if (fread(&i, sizeof(u_int32_t), 1, fp) != 1)
    goto bad;

  if ((i = ntohl(i)) != _CTYPE_REV)
    goto bad;

  if (fread(&len, sizeof(u_int32_t), 1, fp) != 1)
    goto bad;

  if ((len = ntohl(len)) != _CTYPE_NUM_CHARS)
    goto bad;

  if ((new_ctype = malloc(sizeof(UINT16) * (1 + len))) == NULL)
    goto bad;

  new_ctype[0] = 0;
  if (fread(&new_ctype[1], sizeof(UINT16), len, fp) != len)
    goto bad;

  if ((new_toupper = malloc(sizeof(UINT8) * (1 + len))) == NULL)
    goto bad;

  new_toupper[0] = (UINT8)EOF;
  if (fread(&new_toupper[1], sizeof(UINT8), len, fp) != len)
    goto bad;

  if ((new_tolower = malloc(sizeof(UINT8) * (1 + len))) == NULL)
    goto bad;

  new_tolower[0] = (UINT8)EOF;
  if (fread(&new_tolower[1], sizeof(UINT8), len, fp) != len)
    goto bad;

#if BYTE_ORDER == LITTLE_ENDIAN
  for (i = 1; i <= len; i++) {
    new_ctype[i] = ntohs(new_ctype[i]);
  }
#endif

  (void) fclose(fp);
  if (_cClass != _C_CharClassTable)
    free(__UNCONST(_cClass));
  _cClass = new_ctype;
  if (_uConvT != _C_ToUpperTable)
    free(__UNCONST(_uConvT));
  _uConvT = new_toupper;
  if (_lConvT != _C_ToLowerTable)
    free(__UNCONST(_lConvT));
  _lConvT = new_tolower;

  return 1;
bad:
  free(new_tolower);
  free(new_toupper);
  free(new_ctype);
  (void) fclose(fp);
  return 0;
}