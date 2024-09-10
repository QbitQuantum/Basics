static int exec(FILE* fp, ENC_INFO* einfo)
{
#define NCOL  8

  int c, val, enc;

  enc = einfo->num;

  fprintf(fp, "static const unsigned short Enc%s_CtypeTable[256] = {\n",
	  einfo->name);

  for (c = 0; c < 256; c++) {
    val = 0;
    if (IsNewline(enc, c))  val |= BIT_CTYPE_NEWLINE;
    if (IsAlpha (enc, c))   val |= (BIT_CTYPE_ALPHA | BIT_CTYPE_ALNUM);
    if (IsBlank (enc, c))   val |= BIT_CTYPE_BLANK;
    if (IsCntrl (enc, c))   val |= BIT_CTYPE_CNTRL;
    if (IsDigit (enc, c))   val |= (BIT_CTYPE_DIGIT | BIT_CTYPE_ALNUM);
    if (IsGraph (enc, c))   val |= BIT_CTYPE_GRAPH;
    if (IsLower (enc, c))   val |= BIT_CTYPE_LOWER;
    if (IsPrint (enc, c))   val |= BIT_CTYPE_PRINT;
    if (IsPunct (enc, c))   val |= BIT_CTYPE_PUNCT;
    if (IsSpace (enc, c))   val |= BIT_CTYPE_SPACE;
    if (IsUpper (enc, c))   val |= BIT_CTYPE_UPPER;
    if (IsXDigit(enc, c))   val |= BIT_CTYPE_XDIGIT;
    if (IsWord  (enc, c))   val |= BIT_CTYPE_WORD;
    if (IsAscii (enc, c))   val |= BIT_CTYPE_ASCII;

    if (c % NCOL == 0) fputs("  ", fp);
    fprintf(fp, "0x%04x", val);
    if (c != 255) fputs(",", fp);
    if (c != 0 && c % NCOL == (NCOL-1))
      fputs("\n", fp);
    else
      fputs(" ", fp);
  }
  fprintf(fp, "};\n");
  return 0;
}