static void tokencat ( char c ) {
  if ( is_lower ( c ) ) {
    c = _toupper ( c );
  }
  char *eot = strchr ( g_sb_token, '\0' );
  *eot = c;
  *(eot + 1) = '\0';
}