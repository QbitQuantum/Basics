int check_error(int err, char *prompt, char *msg) {
   if (err != Z_OK) {
      Fprintf(stderr, "%s error: %d", prompt, err);
      if (msg) Fprintf(stderr, "(%s)", msg);
      Fprintf(stderr, "\n");
      return 1;
   }
   return 0;
}