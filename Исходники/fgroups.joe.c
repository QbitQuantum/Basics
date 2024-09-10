int main()
{
  FILE *fp = fopen("test.txt", "r");
  int c = 0;
  int i = 0;
  char s[512];
  Table_T our_table = Table_new(10, NULL, NULL);
  char * name;
  const char *fingerprint;
  const char* temp;
  while((c=fgetc(fp)) != ' ' && c != EOF)  //Fingerprint section
    {
      s[i]= c;
      i++;
    }
  s[i] = '\0';
  //Here we have fingerprint in s
  fingerprint = Atom_string(s);
  temp = Atom_string(s); 
  i = 0;
  while((c = getc(fp)) != '\n' && c != EOF)
    {
      s[i] = c;
      i++;
    }
  s[i] = '\0';
  //Here we have name in s
  name = s;    
  Table_put(our_table, fingerprint, name);
  while( c != EOF)
    {
      i = 0;
      while((c = fgetc(fp)) != ' ' && c != EOF) // Fingerprint section
	{
	  s[i] = c;
          i++;
	}
       s[i] = '\0';
       fingerprint = Atom_string(s);
       i = 0;
       while((c = getc(fp)) != '\n' && c != EOF)
	   {
             s[i] = c;
             i++;
            }
        s[i] = '\0';
        name = s;
        printf("FP: %s\n ", fingerprint);
    printf("NAME: %s\n", name);
 
	char * test = Table_put(our_table, fingerprint, name);
        printf("idk: %s\n", test); 
	// printf("VALUE STORED IN FP: %s\n\n", (char *)Table_get(our_table, temp));   
  }

  // NEED TO DEAL WITH TABLE MAP AND IMPLEMENTING A LIST   
  // Table_map(our_table, vfree, NULL);
  
  //printf("%s", fingerprint);
  // printf("%s", (char *)Table_get(our_table, fingerprint));
  
  printf("%d", Table_length(our_table));
  
  // Table_map(our_table, vfree, NULL);
  int length = Table_length(our_table);
  void **table = Table_toArray(our_table, NULL);
 for(int x = 0; x < 2*length; x++)
    {
      printf("%s ", (char *)table[x]); 
   }


  Table_free(&our_table);
  return 0;
}