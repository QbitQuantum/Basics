int main(int argc, char const *argv[])
{
  int len, n, i;
  char word[MAXWORD];


  printf("%d\n", sizeof("abcd"));

  return 0;
  
  while((len = getword(word, MAXWORD)) >= 0)
  {
    if (ISALPHA(word[0]))
    {
      if ((n = binsearch(word, keytab, NKEYS)) > 0)
      {
        keytab[n].count++;
      }
    }
  }

  for (i = 0; i < NKEYS; ++i)
  {
    printf("%s: %d\n", keytab[i].word, keytab[i].count);
  }

  return 0;
}