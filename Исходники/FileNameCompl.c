BOOL FileNameComplete(Object *obj, BOOL backwards, struct InstData *data)
{
  BOOL edited = FALSE;

  ENTER();

  if(data->FNCBuffer != NULL)
  {
    if(data->FileEntries == 1)
    {
      DisplayBeep(NULL);
    }
    else
    {
      if(backwards)
      {
        if(--data->FileNumber < 0)
          data->FileNumber = data->FileEntries-1;
      }
      else
      {
        if(++data->FileNumber >= data->FileEntries)
          data->FileNumber = 0;
      }
    }
    InsertFileName(data->FileNameStart, data);
    edited = TRUE;
  }
  else
  {
    LONG pos = DoMethod(obj, MUIM_BetterString_FileNameStart, data->Contents, data->BufferPos);

    switch(pos)
    {
      case MUIR_BetterString_FileNameStart_Volume:
      {
        struct DosList *dl;
        STRPTR volumeName = NULL;
        char tmpBuffer[256];
        UWORD cut;

        pos = VolumeStart(data->Contents, data->BufferPos);
        if((cut = data->BufferPos-pos) != 0)
        {
          dl = LockDosList(LDF_READ|LDF_DEVICES|LDF_VOLUMES|LDF_ASSIGNS);
          while((dl = NextDosEntry(dl, LDF_READ|LDF_DEVICES|LDF_VOLUMES|LDF_ASSIGNS)) != NULL)
          {
            #ifdef __AROS__
            strlcpy(tmpBuffer, dl->dol_Ext.dol_AROS.dol_DevName, sizeof tmpBuffer);
            #else
            // dol_Name is a BSTR, we have to convert it to a regular C string
            char *bstr = BADDR(dl->dol_Name);

            // a BSTR cannot exceed 255 characters, hence the buffer size of 256 is enough in any case
            strlcpy(tmpBuffer, &bstr[1], (unsigned char)bstr[0]);
            #endif

            if(Strnicmp(tmpBuffer, data->Contents+pos, cut) == 0)
            {
              volumeName = tmpBuffer;
              break;
            }
          }

          if(volumeName != NULL)
          {
            if(OverwriteA(volumeName, pos, cut, strlen(volumeName)+1, data))
              data->Contents[data->BufferPos-1] = ':';
            edited = TRUE;
          }
          UnLockDosList(LDF_READ|LDF_DEVICES|LDF_VOLUMES|LDF_ASSIGNS);
        }
      }
      break;

      default:
      {
        struct FNCData *fncbuffer;
        struct FNCData *fncframe;
        struct ExAllControl *control;
        BPTR dirlock;
        char pattern[42];
        UWORD namestart = data->BufferPos;
        char oldletter = '\0';
        BOOL filename = TRUE;

        while(filename)
        {
          switch(*(data->Contents+namestart-1))
          {
            case '/':
            case ':':
              filename = FALSE;
              break;

            default:
              namestart--;
              break;
          }
        }

        if((data->BufferPos-namestart) < 32)
        {
          strlcpy(pattern, data->Contents+namestart, sizeof(pattern));
          strlcat(pattern, "~(#?.info)", sizeof(pattern));

          oldletter = data->Contents[namestart];
          data->Contents[namestart] = '\0';

          if((fncbuffer = (struct FNCData *)SharedPoolAlloc(4100)) != NULL)
          {
            fncbuffer->next = NULL;

            if((control = (struct ExAllControl *)AllocDosObject(DOS_EXALLCONTROL, NULL)))
            {
              char tokenized[sizeof(pattern) * 2 + 2];

              if(ParsePatternNoCase(pattern, tokenized, sizeof(tokenized)) != -1)
                control->eac_MatchString = tokenized;

              if((dirlock = Lock(data->Contents+pos, ACCESS_READ)))
              {
                UWORD entries = 0;

                fncframe = fncbuffer;
                while(fncframe && ExAll(dirlock, &fncframe->buffer, 4096, ED_TYPE, control))
                {
                  entries += control->eac_Entries;

                  if((fncframe->next = (struct FNCData *)SharedPoolAlloc(4100)))
                    fncframe->next->next = NULL;

                  fncframe = fncframe->next;
                }
                control->eac_Entries += entries;

                data->FileNumber = backwards ? control->eac_Entries-1 : 0;
                data->FileEntries = control->eac_Entries;
                data->FileNameStart = namestart;
                data->FNCBuffer = fncbuffer;

                if(control->eac_Entries)
                {
                  data->Contents[namestart] = oldletter;
                  InsertFileName(namestart, data);
                  edited = TRUE;
                }
                UnLock(dirlock);
              }
              else
              {
                SharedPoolFree(fncbuffer);
              }

              FreeDosObject(DOS_EXALLCONTROL, (APTR)control);
            }
          }
        }

        if(edited == FALSE)
          data->Contents[namestart] = oldletter;
      }
      break;
    }
  }

  RETURN(edited);
  return edited;
}