static void add_completer_widget(Widget w, int row)
{
  if (row >= 0)
    {
      if (cmpwids_size <= row)
	{
	  int i;
	  i = cmpwids_size;
	  cmpwids_size = row + 8;
	  if (cmpwids == NULL)
	    cmpwids = (Widget *)CALLOC(cmpwids_size, sizeof(Widget));
	  else 
	    {
	      cmpwids = (Widget *)REALLOC(cmpwids, cmpwids_size * sizeof(Widget));
	      for (; i < cmpwids_size; i++) cmpwids[i] = NULL;
	    }
	}
      cmpwids[row] = w;
    }
}