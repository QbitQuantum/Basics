stock *parse_csv_history_file(char *csv_file)
{

  char *line;
  char *end_line;
  char *ptr;

  int day;
  char smonth[10];
  int month;
  int year;

  char *date;

  int i;
  int test;

  stock *StockPtr=NULL;
  stock *LastStockPtr=NULL;

  /* Used to return the pointer to the list */
  stock *FirstStockPtr=NULL;

  line = csv_file;
  end_line = csv_file;

  /* do not use the first line */
  end_line = strstr(line, "\n");
  *end_line = 0;
  end_line++;
  line = end_line;

  while ((end_line = strstr(line, "\n")))
    {
      *end_line = 0;

      StockPtr = malloc_stock();

      /* Date */
      ptr = strtok(line, ",");
      if (!ptr) return 0;

      sscanf(ptr,"%d-%3s-%d",&day,smonth,&year);

      i=0;

#ifdef __UNIX__
      while((test=strcasecmp(months[i], smonth))) i++;
#elif __WINDOWS__
      while(test=_mbsnbicmp(months[i], smonth, strlen(months[i]))) i++;
#endif

      month = i+1;

      date = (char *)malloc(DATE_LENGTH);
      if (date==NULL)
	{
	  fprintf(stderr,"Memory allocating error (%s line %d)\n"
		  ,__FILE__, __LINE__);
	  exit(1);
	}
      sprintf(date,"%.2d%.2d%.2d", year, month, day);
      StockPtr->Date = date;

      /* Open */
      ptr = strtok(NULL, ",");
      if (!ptr) return 0;
      sscanf(ptr,"%f",&(StockPtr->OpenPrice));

      /* High */
      ptr = strtok(NULL, ",");
      if (!ptr) return 0;
      sscanf(ptr,"%f",&(StockPtr->MaxPrice));

      /* Low */
      ptr = strtok(NULL, ",");
      if (!ptr) return 0;
      sscanf(ptr,"%f",&(StockPtr->MinPrice));

      /* Close */
      ptr = strtok(NULL, ",");
      if (!ptr) return 0;
      sscanf(ptr,"%f",&(StockPtr->LastPrice));

      /* Volume */

      ptr = strtok(NULL, ",");
      if (!ptr)
	/* It seems to be an indice */
	/* No volume for indices */
	StockPtr->Volume = 0;
      else
	StockPtr->Volume = atoi(ptr);

      if( !FirstStockPtr )
	{
	  FirstStockPtr = StockPtr;
	  StockPtr->PreviousStock = 0;
	}

      StockPtr->NextStock = 0;

      if (LastStockPtr)
	{
	  LastStockPtr->NextStock = StockPtr;
	  StockPtr->PreviousStock = LastStockPtr;
	}

      LastStockPtr = StockPtr;

      end_line++;
      line = end_line;
    }

  return (FirstStockPtr);
}