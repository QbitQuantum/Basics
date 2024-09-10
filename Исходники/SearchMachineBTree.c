void smbtree_fscanf(BTree* tree, FILE* file, char* url)
{
  wchar_t* entryWord = malloc(STRING_SIZE * sizeof(wchar_t));
  int pos=1;

  while(fwscanf(file,L"%ls",entryWord) != EOF)
  {
    preprocessador(entryWord);

    if(wcslen(entryWord)!=0)
    {
      char* word = malloc(STRING_SIZE * sizeof(char));
      wcstombs(word, entryWord, STRING_SIZE);
      updateTree(tree, word, pos, url);//INSERIR PALAVRA NA ARVORE
    }
      pos++;
  }

  free(entryWord);
}