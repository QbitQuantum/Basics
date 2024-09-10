/**********************************************************************
 *  Function  basic_alg_menu();
 *                                                                    
 *  Parameter:                                                       
 *   
 *                                                              
 *  This function prompts user to choose a basic algorithm to execute
 *  such as Boyer-Moore.  The utilities menu is also available from
 *  this menu.
 *                                                                   
 **********************************************************************/
void basic_alg_menu()
{
  int i, status, num_lines, alpha_size, num_patterns;
  char ch;
  STRING *text, *pattern, **patterns;

  alpha_size = 0;
  while (1)  {
    num_lines = 22;
    printf("\n**   Basic Search Algorithm Menu    **\n\n");
    printf("1)  Naive Algorithm\n");
    printf("2)  Boyer-Moore Variations\n");
    printf("     a) Bad character rule\n");
    printf("     b) Extended bad character rule\n");
    printf("     c) Good suffix & bad character rules\n");
    printf("     d) Good suffix & extended bad character rules\n");
    printf("3)  Knuth-Morris-Pratt (original preprocessing)\n");
    printf("     a) using sp values\n");
    printf("     b) using sp' values\n");
    printf("4)  Aho-Corasick Set Matching\n");
    printf("5)  Boyer-Moore Set Matching\n");
    printf("     a) Bad character rule only\n");
    printf("     b) Good suffix rule using keyword and suffix trees\n");
    printf("     c) Good suffix rule using suffix tree only\n");
    printf("     d) using original Boyer-Moore (1c) on each pattern\n");
    printf("*)  String Utilites\n");
    printf("0)  Exit\n");
    printf("\nEnter Selection: ");
  
    while ((choice = my_getline(stdin, &ch_len)) == NULL) ;
    switch (choice[0]) {
    case '0':
      return;

    case '1':
      if (!(pattern = get_string("pattern")) || !(text = get_string("text")))
        continue;

      mstart(stdin, fpout, OK, OK, 5, NULL);
      mprintf("\nThe pattern:\n");
      terse_print_string(pattern);
      mprintf("\nThe text:\n");
      terse_print_string(text);
      mputc('\n');
        
      status = map_sequences(text, pattern, NULL, 0);
      if (status != -1) {
        mprintf ("Executing naive search algorithm...\n\n");
        strmat_naive_match(pattern, text, stats_flag);
        unmap_sequences(text, pattern, NULL, 0);
      }
      mend(num_lines);
      putchar('\n');
      break;

    case '2':
      ch = choice[1];
      if (toupper(ch) != 'A' && toupper(ch) != 'B' &&
          toupper(ch) != 'C' && toupper(ch) != 'D') {
        printf("\nYou must specify the Boyer-Moore variation"
               " (as in '2a' or '2c').\n");
        continue;
      }

      if (!(pattern = get_string("pattern")) || !(text = get_string("text")))
        continue;

      mstart(stdin, fpout, OK, OK, 5, NULL);
      mprintf("\nThe pattern:\n");
      terse_print_string(pattern);
      mprintf("\nThe text:\n");
      terse_print_string(text);
      mputc('\n');

      status = map_sequences(text, pattern, NULL, 0);
      if (status != -1) {
        mprintf("Executing Boyer-Moore algorithm...\n\n");
        switch (toupper(ch)) {
        case 'A':  strmat_bmbad_match(pattern, text, stats_flag);  break;
        case 'B':  strmat_bmext_match(pattern, text, stats_flag);  break;
        case 'C':  strmat_bmgood_match(pattern, text, stats_flag);  break;
        case 'D':  strmat_bmextgood_match(pattern, text, stats_flag);  break;
        }
        unmap_sequences(text, pattern, NULL, 0);
      }
      mend(num_lines);
      putchar('\n');
      break;

    case '3':
      ch = choice[1];
      if (toupper(ch) != 'A' && toupper(ch) != 'B') {
        printf("\nYou must specify the KMP variation (as in '3a' or '3b').\n");
        continue;
      }

      if (!(pattern = get_string("pattern")) || !(text = get_string("text")))
        continue;

      mstart(stdin, fpout, OK, OK, 5, NULL);
      mprintf("\nThe pattern:\n");
      terse_print_string(pattern);
      mprintf("\nThe text:\n");
      terse_print_string(text);
      mputc('\n');
        
      status = map_sequences(text, pattern, NULL, 0);
      if (status != -1) {
        if (toupper(ch) == 'A') {
          mprintf ("Executing KMP with sp values...\n\n");
          strmat_kmp_sp_orig_match(pattern, text, stats_flag);
        }
        else {
          mprintf ("Executing KMP with sp' values...\n\n");
          strmat_kmp_spprime_orig_match(pattern, text, stats_flag);
        }
        unmap_sequences(text, pattern, NULL, 0);
      }
      mend(num_lines);
      putchar('\n');
      break;

    case '4':
      if (!(patterns = get_string_ary("list of patterns", &num_patterns)))
        continue;
      if (!(text = get_string("text"))) {
        free(patterns);
        continue;
      }

      mstart(stdin, fpout, OK, OK, 5, NULL);
      mprintf("\nThe patterns:\n");
      for (i=0; i < num_patterns; i++) {
        mprintf("%2d)", i + 1);
        terse_print_string(patterns[i]);
      }
      mprintf("\nThe text:\n");
      terse_print_string(text);
      mputc('\n');

      status = map_sequences(text, NULL, patterns, num_patterns);
      if (status != -1) {
        mprintf("Executing Aho-Corasick algorithm...\n\n");
        strmat_ac_match(patterns, num_patterns, text, stats_flag);
        unmap_sequences(text, NULL, patterns, num_patterns);
      }
      mend(num_lines);
      putchar('\n');

      free(patterns);
      break;

    case '5':
      ch = toupper(choice[1]);
      if (ch != 'A' && ch != 'B' && ch != 'C' && ch != 'D') {
        printf("\nYou must specify the set Boyer-Moore variation"
               " (as in '5a' or '5c').\n");
        continue;
      }

      if (!(patterns = get_string_ary("list of patterns", &num_patterns)))
        continue;
      if (!(text = get_string("text"))) {
        free(patterns);
        continue;
      }

      mstart(stdin, fpout, OK, OK, 5, NULL);
      mprintf("\nThe patterns:\n");
      for (i=0; i < num_patterns; i++) {
        mprintf("%2d)", i + 1);
        terse_print_string(patterns[i]);
      }
      mprintf("\nThe text:\n");
      terse_print_string(text);
      mputc('\n');

      status = map_sequences(text, NULL, patterns, num_patterns);
      if (status != -1) {
        mprintf("Executing Boyer-Moore set matching algorithm...\n\n");
        switch (toupper(ch)) {
        case 'A':  strmat_bmset_badonly_match(patterns, num_patterns,
                                              text, stats_flag);       break;
        case 'B':  strmat_bmset_2trees_match(patterns, num_patterns,
                                             text, stats_flag);        break;
        case 'C':  strmat_bmset_1tree_match(patterns, num_patterns,
                                            text, stats_flag);         break;
        case 'D':  strmat_bmset_naive_match(patterns, num_patterns,
                                            text, stats_flag);         break;
        }
        unmap_sequences(text, NULL, patterns, num_patterns);
      }
      mend(num_lines);
      putchar('\n');

      free(patterns);
      break;

    case '*':
      util_menu();
      break;

    default:
      printf("\nThat is not a choice.\n");
    }
  }
}