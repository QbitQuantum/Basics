void editfile (list_ref list, char *filename) {
   char stdinline[1024];
   int stdincount = 0;
   for(;; ++stdincount) {
      printf ("%s: ", Exec_Name);
      char *linepos = fgets (stdinline, sizeof stdinline, stdin);
      if (linepos == NULL) break;
      if (want_echo) printf ("%s", stdinline);
      linepos = strchr (stdinline, '\n');
      if (linepos == NULL || stdinline[0] == '\0') {
         badline (stdincount, stdinline);
      }else {
         *linepos = '\0';
         switch (stdinline[0]) {
            case '$': setmove_list(list, MOVE_LAST, stdinline); break;
            case '*': print_all(list, stdinline); break;
            case '.': viewcurr_list(list, stdinline); break;
            case '0': setmove_list(list, MOVE_HEAD, stdinline); break;
            case '<': setmove_list(list, MOVE_PREV, stdinline); break;
            case '>': setmove_list(list, MOVE_NEXT, stdinline); break;
            case '@': debugdump_list (list, stdinline); break;
            case 'a': insert_line_after (list, stdinline+1); break;
            case 'd': delete_list(list, stdinline); break;
            case 'i': insert_line_before(list, stdinline+1); break;
            case 'r': insertfile(list, stdinline+1); break;
            case 'w': writefile (list, stdinline+1, filename); break;
            default : badline (stdincount, stdinline);
         }
      }
   }
   printf("%s\n", "^D");
}