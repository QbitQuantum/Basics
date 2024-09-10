void LoadLayerTypeInfo(CCEtoODBDoc *doc, const char *filename)
{
   CWaitCursor();
   
	// try reading an xml layertype file first
	LayerTypeXMLReader reader(*doc);
	FileStatusTag retval = reader.open(filename);

	// if not successful, then assume its the old one
	if (retval == statusSucceeded)
	{
		// init
		for (int i=0; i<MAX_LAYERSETS; i++)
		{
			for (int j=0; j<MAX_LAYTYPE; j++)
			{
				doc->LayerTypeArray[i][j].color = RGB(255, 255, 255);
				doc->LayerTypeArray[i][j].show = false;
			}
		}

		//reader.setDoc(doc);

		retval = reader.parse();
		
		return;
	}

	FILE *stream;
   if ((stream = fopen(filename, "rt")) == NULL)
   {
      ErrorMessage(filename, "Unable to open file");
      return;
   }

   char     line[500], *tok;
   int      i, j;
   int      version = 1;

   if (fgets(line,500,stream) == NULL)
      return;

   if (strcmp(line, "! Layertype Information\n"))
   {
      if (!strcmp(line, "! Layertype Information V2\n"))
      {
         version = 2;
      }
      else
      if (!strcmp(line, "! Layertype Information V3\n"))
      {
         version = 3;
      }
      else
      {
         ErrorMessage("This is not a Layertype Information File");
         return;
      }
   }

   // init
   for (i=0; i<MAX_LAYERSETS; i++)
   {
      for (j=0; j<MAX_LAYTYPE; j++)
      {
         doc->LayerTypeArray[i][j].color = RGB(255, 255, 255);
         doc->LayerTypeArray[i][j].show = false;
      }
   }

   if (version == 1)
   {
      int red, green, blue;
      for (i=0; i<MAX_LAYERSETS; i++)  // Normal, Top, Bottom, Cust 1, 2, 3, 4, 5
      {
         j=0;
         while (j<31)   // this was 31 before version 2
         {
            if (fgets(line,500,stream) == NULL) return;
   
            if (line[0] == '!' || line[0] == '\n') continue; // remark

            if ((tok = strtok(line, " \t\n(),")) == NULL) continue;
            doc->LayerTypeArray[i][j].show = atoi(tok);

            if ((tok = strtok(NULL, " \t\n(),")) == NULL) continue;
            red = atoi(tok);

            if ((tok = strtok(NULL, " \t\n(),")) == NULL) continue;
            green = atoi(tok);

            if ((tok = strtok(NULL, " \t\n(),")) == NULL) continue;
            blue = atoi(tok);

            doc->LayerTypeArray[i][j].color = RGB(red, green, blue);

            j++;
         }
      }
   }
   else
   if (version >= 2)
   {
      int red, green, blue;
         
      while (fgets(line,500,stream) != NULL) 
      {
         if (line[0] == '!' || line[0] == '\n') continue; // remark

         if ((tok = strtok(line, " \t\n(),")) == NULL) continue;

         if (!STRCMPI(tok,".NAME"))
         {
            CString  colorsetname;
            if ((tok = strtok(NULL, " \t")) == NULL) continue;
            int id = atoi(tok);
            if ((tok = strtok(NULL, "\n")) == NULL) continue;
            colorsetname = tok;
            colorsetname = tok;
            colorsetname.TrimLeft();
            colorsetname.TrimRight();
            doc->CustomLayersetNames.SetAt(id, tok);
         }
         else
         {
            i = atoi(tok);
            if (i >= MAX_LAYERSETS)
               continue;

            if ((tok = strtok(NULL, " \t\n(),")) == NULL) continue;
            j = atoi(tok);
            if (j >= MAX_LAYTYPE)
               continue;

            if ((tok = strtok(NULL, " \t\n(),")) == NULL) continue;
            doc->LayerTypeArray[i][j].show = atoi(tok);

            if ((tok = strtok(NULL, " \t\n(),")) == NULL) continue;
            red = atoi(tok);

            if ((tok = strtok(NULL, " \t\n(),")) == NULL) continue;
            green = atoi(tok);

            if ((tok = strtok(NULL, " \t\n(),")) == NULL) continue;
            blue = atoi(tok);
            doc->LayerTypeArray[i][j].color = RGB(red, green, blue);
         }
      }
   }
   fclose(stream);
}