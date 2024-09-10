void DtPrinterIcon::DndCB(BaseUI *obj, char **value, int * /*len*/,
			  DNDProtocol dndProtocol)
{
   DtPrinterIcon *printer;
   if (obj->UIClass() == ICON)
      printer = (DtPrinterIcon *)obj;
   else
      printer = (DtPrinterIcon *)obj->Parent();
   DtActionArg ap[1];
   char *old_LPDEST = NULL;
   ap[0].argClass = DtACTION_FILE;

   char *buf = new char[100];
   switch (dndProtocol)
   {
   case FILENAME_TRANSFER: // Dropping an Object on a printer
      ap[0].u.file.name = *value;
      if (printer->PrintActionExists())
         sprintf(buf, "%s_Print", printer->queue->Name());
      else
       {
	 if (old_LPDEST = STRDUP(getenv("LPDEST")))
	  {
            sprintf(buf, "LPDEST=%s", printer->queue->Name());
	    putenv(buf);
	  }
         strcpy(buf, "Print");
       }

      DtActionInvoke(((AnyUI *)printer->mainw->Parent())->BaseWidget(), buf, ap,
		     1, NULL, NULL, NULL, True, NULL, NULL);
      if (old_LPDEST)
       {
	 sprintf(buf, "LPDEST=%s", old_LPDEST);
	 putenv(buf);
	 delete old_LPDEST;
       }
      break;
   case CONVERT_DATA: // Dragging a printer to an object
      if (printer->PrintActionExists())
       {
	 struct stat statbuff;
         *value = new char[strlen(homeDir) + strlen(PRINTERS_PERSONAL_DIR) +
			   strlen(printer->queue->Name()) + 10];
         sprintf(*value, "%s/%s/%s_Print", homeDir, PRINTERS_PERSONAL_DIR,
		 printer->queue->Name());
	 if (stat(*value, &statbuff) < 0)
	  {
	    int fd = creat(*value, 0755);
	    close(fd);
	  }
       }
      else
	 *value = NULL;
      break;
   case DROP_ON_ROOT:
      {
      char *x = *value;
      char *y = strchr(x, '\n');
      *y++ = '\0';
      char *filename = strchr(y, '\n');
      *filename++ = '\0';
      char *work_space = strchr(filename, '\n');
      if (work_space)
         *work_space++ = '\0';
      }
      break;
   case TEXT_TRANSFER:
      break;
   case BUFFER_TRANSFER:
      *value = new char[strlen(printer->queue->Name()) + 10];
      sprintf(*value, "%s_Print", printer->queue->Name());
      break;
   case CONVERT_DELETE:
      break;
   case ANIMATE:
      break;
   }
   delete [] buf;
}