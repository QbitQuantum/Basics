int main()
{
  char choice;
  char name[80];
  int number;
  int found;
  SymbolTable book;
  int i;
  /* initialize phone book */
  book = createSymbolTable(&makePhoneBook, &comparePhone);

  do{
    choice = getMenu();
    switch(choice){

    case '1':
      printf("Enter the name: ");
      scanf("%[^\n]", name);
      myfflush();
      printf("Enter the number: ");
      scanf("%d", &number);
      myfflush();
      addEntry(&number, &name, &book);
      printf("%d\n", book.total);
      break;

    case '2':
      printf("Enter the number you want to find: ");
      scanf("%d", &number);
      myfflush();
      found = getEntryValue(&number, &book);
      if(found == -1) printf("Not found\n");
      else{
	displayTitle();
	displayEntry(book.entries[found]);
      }      
      break;

    case '3':
      displayTitle();
      for(i = 0; i < book.current; i++){
	displayEntry(book.entries[i]);
      }
      break;

    case '4':
      dropSymbolTable(&book);
      break;
      
    default: printf("Invalid choice\n");
    }
  }while(choice != EXIT);
}