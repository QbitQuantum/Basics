/*
 * ============================================================
 */
int countLetter(char * file1, char * file2)
/*
 * The function counts the occurrences of the twenty sixe English
 * characters and write the results to another file.  
 *
 * file1: name of the input file
 * file2: name of the output file
 *
 * All upper-case letters are converted to lower-case letters. 'A' and
 * 'a' are both counted as 'a'.
 *
 * file1: name of the input file
 * file2: name of the output file
 *
 * This function returns EXIT_SUCCESS if it finishes without any
 * problem. The function returns EXIT_FAILURE if there is a problem in
 * opening the file, reading from the input file, or writing to the
 * output file.
 */
/*
 * You should NOT write anything like the following. You will lose
 * 20% points if you do so.
 *
 * if (c == 'a') ...
 * if (c == 'b') ...
 * if (c == 'c') ...
 * if (c == 'd') ...
 * 
 *
 * You should not write anything like the following, either.
 * switch (c)
 * {
 *  case 'a':
 *  ...
 *  case 'b':
 *  ...
 *  case 'c':
 *  ...
 *  }
 *
 * This is error-prone (what happens if you forget to change one
 * place?).  You should find a general method that is applicable to
 * all 26 characters.
 *
 * Whenever you copy-paste code, you have a higher chance of mistakes.
 *
 * Hint: create an array to store the counts.  Remember to initialize
 * the array's elements.
 *
 * Hint: C has several functions that can be useful.  Check isalpha,
 * isupper, islower.
 * 
 */
{
  FILE *fin = fopen(file1, "r");
  if(fin == NULL)
  {
    return EXIT_FAILURE;
  }

  FILE *fout = fopen(file2, "w");
  if(fout == NULL)
  {
    fclose(fin);
    return EXIT_FAILURE;
  }

  int counts[NUM_CHAR] = {0};
  int c;
  while((c = fgetc(fin)) != EOF)
  {
    if(isupper(c))
    {
      counts[c - 'A']++;
    }
    else if (islower(c))
    {
      counts[c-'a']++;
    }
  }
  int i;
  for(i=0; i< NUM_CHAR; i++)
  {
    fprintf(fout, "%c: %d\n", i+'a', counts[i]);
  }
  
  fclose(fin);
  fclose(fout);


  return EXIT_SUCCESS;
}