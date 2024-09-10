int main()
{
  char data_type[MAX_TOKEN_LENGTH];

  for (line = 1, n_errors = 0; gettoken() != EOF; line++)
    {
      /* 1st token is data declaration type */
      strcpy(data_type, token.value);
      description[0] = '\0';
      declaration();
      if (token.type != DECLARATION_END)
        {
          fprintf(stderr, "Syntax error on line %d\n", line);
          n_errors++;
        }
      printf("%s is a %s %s\n", name, description, data_type);
    }
  exit(n_errors);
}