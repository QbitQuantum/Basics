//search for all words given in file_name and save results to output_file_name
void search_words(TREE_NODE *root, char * file_name, char * output_file_name){
  FILE *file, *output_file;
  file = fopen(file_name,"r");
  output_file = fopen(output_file_name,"w");
  if(!file){
    printf("arquivo de entrada invalido\n");
    return;
  }
  if(!output_file){
    printf("arquivo de saida invalido\n");
    return;
  }

  wchar_t line [ 10000 ];

  wchar_t *result = malloc(sizeof(wchar_t) * 10000);

  //start benchmark
  double start_time, end_time, time_elapsed;
  start_time = (double)clock();

  while ( fgetws ( line, sizeof line, file ) != NULL ){//read line by line
    if(line[wcslen(line) -1] == '\n') line[wcslen(line) -1] = '\0';//remove new line char
    if(line[wcslen(line) -1] == ' ') line[wcslen(line) -1] = '\0';
    W_TOKEN *token = malloc(sizeof(W_TOKEN));
    str_to_lower(line);
    token->word = line;
    search_word(root, token, result);
    fwprintf(output_file, L"%ls",result);
    fputws ( result, stdout );
  }

  end_time = (double)clock();
  time_elapsed = ( end_time - start_time )/CLOCKS_PER_SEC;
  //end benchmark

  fwprintf(output_file, L"%s","\n");
  fwprintf(output_file, L"O tempo gasto na busca foi de %fms.\n", time_elapsed*1000);
  printf("\n");
  printf("O tempo gasto na busca foi de %fms.\n", time_elapsed*1000);

  fclose(file);
  fclose(output_file);

}