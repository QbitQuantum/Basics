static void unsignedHexadecimal(void)
{
  /* FORM: integer-number = decimal-integer | hexadecimal-integer |
   *       binary-integer
   * FORM: hexadecimal-integer = '$' hex-digit-sequence
   * FORM: hex-digit-sequence = hex-digit { hex-digit }
   * FORM: hex-digit = digit | 'a' | 'b' | 'c' | 'd' | 'e' | 'f'
   *
   * On entry, inChar is '$'
   */

  /* This is another representation for an integer */

  token = tINT_CONST;

  /* Loop to process each hex 'digit' */

  for (;;)
    {
      /* Get the next character */

      getCharacter();

      /* Is it a decimal digit? */

      if (isdigit(inChar))
        *stringSP++ = inChar;

      /* Is it a hex 'digit'? */

      else if ((inChar >= 'A') && (inChar <= 'F'))
        *stringSP++ = inChar;

      else if ((inChar >= 'a') && (inChar <= 'f'))
        *stringSP++ = _toupper(inChar);

      /* Otherwise, that must be the end of the hex value */

      else break;
    }

  /* Terminate the hex string and convert to binary using sscanf */

  *stringSP++ = '\0';
  (void)sscanf(tkn_strt, "%lx", &tknInt);

  /* Remove the hex string from the character identifer stack */

  stringSP = tkn_strt;
}