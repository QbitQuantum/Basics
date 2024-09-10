int main()
{
  int buffer_size = 2048;
  int counter = 0;
  int n_newline = 0;
  char *input = (char*) malloc(sizeof(char) * buffer_size);

  if (input == NULL)
    {
      fprintf(stderr, "Error allocating memory.");
      exit(1);
    }

  int c = 0;
  while(1)
    {
      c = getc(stdin);
      if ( c == EOF)
	break;
      
      input[counter] = (char) c;
      counter++;

      if (counter == buffer_size)
	{
	  input = (char*) realloc(input, buffer_size * 2);
	  if (input == NULL)
	    {
	      fprintf(stderr, "Error reallocating memory.");
	      exit(1);
	    }
	  buffer_size *= 2;
	}
    }
  
  if (counter == 0)
    exit(0);
  
  if (input[counter -1] != '\n')
    {
      if (counter == buffer_size)
	{
	  input = (char*) realloc(input, buffer_size * 2);
	  if (input == NULL)
	    {
	      fprintf(stderr, "Error reallocating memory.");
	      exit(1);
	    }
	  buffer_size *= 2;
	}
      input[counter] = '\n';
      counter++;
    }
  
  
  for (int k = 0; k < counter; k++)
    {
      if (input[k] == '\n')
	n_newline++;
    }

  char **helper = (char**)malloc(sizeof(char*) * counter);
  if (helper == NULL)
    {
      fprintf(stderr, "Error allocating memory.");
      exit(1);
    }

  char *pointer = input;
  int pos = 0;
  for (int i = 0; i < n_newline; i++)
    {
      if ( i == 0 && *pointer == '\n')
	{
	  helper[pos] = pointer;
	  pos++;
	  i++;
	  pointer++;
	}
      helper[pos] = pointer;
      pos++;
      while (*pointer != '\n')
	pointer++;
      pointer++;
    }

  qsort(helper, n_newline, sizeof(char*), cmp);

  char *temp;
  for (int k = 0; k < n_newline; k++)
    {
      temp = helper[k];
      while (*temp != '\n')
	{
	  printf("%c", *temp);
	  temp++;
	}
      printf("%c", *temp);
    }

  free(input);
  free(helper);
  return 0;

}