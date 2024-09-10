//load words into an avl tree
TREE_NODE * index_file(char *file_name){
  FILE *file;
  file = fopen(file_name,"r");
  if(!file){
    printf("arquivo de entrada invalido\n");
    return NULL;
  }

  wchar_t line [ 10000 ];
  wchar_t *token;
  wchar_t *state;
  const wchar_t delimiters[] = L" \n,.;'\"?-|:*&!@$%{}()[]<>\\";//only consider letters
  int current_line = 1;
  TREE_NODE *tree = NULL;
  W_TOKEN *w_token = NULL;

  while ( fgetws ( line, sizeof(line), file ) ){//read line by line
    for (token = wcstok(line, delimiters, &state);
           token != NULL;
           token = wcstok(NULL, delimiters, &state)) {
      if(token) w_token = create_word(token);
      insert_avl(&tree, (void *)w_token, lex_order, current_line);
      }
    current_line++;
  }

  fclose ( file );
  return tree;
}