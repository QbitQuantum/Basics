LONG SmartReadArgs(struct WBStartup * wb_startup, struct SmartArgs * args)
{
   LONG error;

   args->sa_Flags = 0;

   D(bug("UtilityBase = 0x%lx\n", (ULONG) UtilityBase));
   D(bug("IconBase    = 0x%lx\n", (ULONG) IconBase));
   D(bug("WBStartup   = 0x%lx\n", (ULONG) wb_startup));

   if (wb_startup != NULL)
   {
      struct WBArg *wbarg = wb_startup->sm_ArgList;
      LONG arg_counter = 0;

      D(bug("  numArgs   = %ld\n", wb_startup->sm_NumArgs));
      while (arg_counter < wb_startup->sm_NumArgs)
      {
         D(bug("  name[%ld] = \"%s\"\n", arg_counter, wbarg->wa_Name));
         wbarg += 1;
         arg_counter += 1;
      }
   }

   if (wb_startup != NULL)
   {
      if (!(args->sa_RDArgs = AllocDosObject(DOS_RDARGS, NULL)))
      {
         return (ERROR_NO_FREE_STORE);
      }
      else
      {
         args->sa_Flags |= SAF_ALLOCRDARGS;

         if (!args->sa_Buffer)
         {
            args->sa_BufferSize = MAX(SA_MINIMUM_BUFFER_SIZE, args->sa_BufferSize);
            args->sa_Buffer = AllocMem(args->sa_BufferSize, MEMF_ANY);
            args->sa_Flags |= SAF_ALLOCBUFFER;
         }

         if (!args->sa_Buffer)
            return (ERROR_NO_FREE_STORE);
         else
         {
            struct DiskObject *dobj;

            args->sa_ActualPtr = args->sa_Buffer;
            args->sa_EndPtr = args->sa_Buffer + args->sa_BufferSize - 1;

            if (!(dobj = smart_get_icon(args, wb_startup)))
            {
               return (ERROR_OBJECT_NOT_FOUND);
            }
            else
            {
               struct WBArg *wbarg = args->sa_WBArg;
               ULONG num = args->sa_NumArgs;

               STRPTR *tooltypes = (STRPTR *) dobj->do_ToolTypes;
               STRPTR name;
               STRPTR temp;
               STRPTR ptr;

               if (num > 1 && args->sa_FileParameter >= 0 && (temp = AllocMem(TEMPSIZE, MEMF_ANY)))
               {
                  ULONG modes = 0;

                  get_arg_name(args, temp, TEMPSIZE, &modes);
                  fstrcpy(args, temp);
                  fstrcpy(args, " ");

                  /* no "/M" specifier in the ReadArgs() template, thus use only the first file */
                  if (modes != MODE_MULTI)
                     num = 2;

                  while (num > 1)
                  {
                     get_wbarg_name(wbarg, temp, TEMPSIZE);
                     fstrcpy(args, "\"");
                     fstrcpy(args, temp);
                     fstrcpy(args, "\" ");
                     num--;
                     wbarg++;
                  }

                  FreeMem(temp, TEMPSIZE);
               }

               D(bug("tooltypes=%lx\n", (ULONG) tooltypes));
               if (tooltypes)
               {
                  while (*tooltypes)
                  {
                     ptr = *tooltypes;
                     name = ptr;

                     /* check if this tooltype enabled and part of the
                      * template */
                     if ((*ptr != '(')
                         && is_in_template(name, args->sa_Template))
                     {
                        while (*ptr != '=' && *ptr != EOS)
                           ptr++;

                        if (*ptr == '=')
                        {
                           *ptr = EOS;

                           if (!Stricmp(name, "WINDOW"))
                           {
                              STRPTR win;
                              if ((win = AllocVec(strlen(ptr + 1) + 1, MEMF_ANY)))
                              {
                                 strcpy(win, ptr + 1);
                                 args->sa_Window = win;
                                 args->sa_Flags |= SAF_ALLOCWINDOW;
                              }

                           }
                           else
                           {
                              fstrcpy(args, name);

                              /* enclose the argument in "" */
                              if (*(ptr + 1) == '"')
                              {
                                 fstrcpy(args, "=");
                                 fstrcpy(args, ptr + 1);
                              }
                              else
                              {
                                 fstrcpy(args, "=\"");
                                 fstrcpy(args, ptr + 1);
                                 fstrcpy(args, "\"");
                              }

                              *ptr = '=';
                           }
                        }
                        else
                           fstrcpy(args, name);

                        fstrcpy(args, " ");
                     }
                     tooltypes++;
                  }             /* while (*tooltypes) */
               }                /* if (tooltypes) */
               fstrcpy(args, "\n");

               D(bug("final wb command line : \"%s\"\n", args->sa_Buffer));
            }
         }
      }

      args->sa_RDArgs->RDA_Source.CS_Buffer = args->sa_Buffer;
      args->sa_RDArgs->RDA_Source.CS_Length = strlen(args->sa_Buffer);

      args->sa_Flags |= SAF_WORKBENCH;
   }

   args->sa_FreeArgs = ReadArgs(args->sa_Template, args->sa_Parameter, args->sa_RDArgs);

   if (SetSignal(0L, SIGBREAKF_CTRL_C) & SIGBREAKF_CTRL_C)
   {
      SetIoErr(ERROR_BREAK);
   }

   if ((error = IoErr()) == 0 && (wb_startup != NULL))
   {
      if (args->sa_Window)
      {
         args->sa_WindowFH = Open(args->sa_Window, MODE_NEWFILE);
         if (args->sa_WindowFH)
         {
            args->sa_OldOutput = SelectOutput(args->sa_WindowFH);
            args->sa_OldInput = SelectInput(args->sa_WindowFH);
         }
      }
   }

   return (error);
}