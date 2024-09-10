//------------------------------------------------------------------------------
void Scan_registry_deletedKey_file(char *reg_file,unsigned int session_id,sqlite3 *db)
{
  //open file
  HANDLE Hfic = CreateFile(reg_file,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,0);
  if (Hfic == INVALID_HANDLE_VALUE)return;

  DWORD taille_fic = GetFileSize(Hfic,NULL);
  if (taille_fic<1 || taille_fic == INVALID_FILE_SIZE)
  {
    CloseHandle(Hfic);
    return;
  }

  //alloc memory
  char *buffer = (char *) HeapAlloc(GetProcessHeap(), 0, taille_fic+1);
  if (!buffer)
  {
    CloseHandle(Hfic);
    return;
  }

  //load file
  DWORD copiee, position = 0, increm = 0;
  if (taille_fic > DIXM)increm = DIXM;
  else increm = taille_fic;

  while (position<taille_fic && increm!=0)
  {
    copiee = 0;
    ReadFile(Hfic, buffer+position, increm,&copiee,0);
    position +=copiee;
    if (taille_fic-position < increm)increm = taille_fic-position ;
  }
  CloseHandle(Hfic);

  //working
  if (position>0)
  {
    if (((REGF_HEADER*)buffer)->id == 0x66676572) //Fichier REG standard
    {
      taille_fic = position;
      position = 0x1000; //first hbin struct

      HBIN_HEADER *hb_h;
      DWORD pos_fhbin = 0;

      //recherche du 1er hbin !! (en cas de bug)
      while(position<taille_fic-4)
      {
        hb_h = (HBIN_HEADER *)&buffer[position];
        if (hb_h->id == 0x6E696268 )  //hbin
        {
          if (pos_fhbin == 0)pos_fhbin = position;
          position=position+HBIN_HEADER_SIZE;//entête hbin
          break;
        }else position++;
      }

      HBIN_CELL_PRE_HEADER *hb_ph;
      while(position<taille_fic-(HBIN_CELL_PRE_HEADER_SIZE+1))
      {
        //on ne traite que les clés nk (name key = directory)
        hb_ph = (HBIN_CELL_PRE_HEADER *)&buffer[position];
        if (((hb_ph->size[1]&0xFF) == 0xFF) && ((hb_ph->size[2]&0xFF) == 0xFF) && ((hb_ph->size[3]&0xFF) == 0xFF))
        {
          switch(hb_ph->type)
          {
            case 0x6B6E:  position = position + Traiter_RegBin_nk_deleted(reg_file, position, taille_fic, buffer,session_id,db,FALSE);break; //nk
            case 0x6B73 : if (position + HBIN_CELL_SK_SIZE < taille_fic)position = position + HBIN_CELL_SK_SIZE;else position++;break;//sk
            case 0x6B76 : if (position + HBIN_CELL_VK_SIZE < taille_fic)position = position + HBIN_CELL_VK_SIZE;else position++;break;//vk
            case 0x666C : if (position + HBIN_CELL_LF_SIZE < taille_fic)position = position + HBIN_CELL_LF_SIZE;else position++;break;//lf
            case 0x686C : if (position + HBIN_CELL_LH_SIZE < taille_fic)position = position + HBIN_CELL_LH_SIZE;else position++;break;//lh
            case 0x696C : if (position + HBIN_CELL_LI_SIZE < taille_fic)position = position + HBIN_CELL_LI_SIZE;else position++;break;//li
            case 0x6972 : if (position + HBIN_CELL_RI_SIZE < taille_fic)position = position + HBIN_CELL_RI_SIZE;else position++;break;//ri
            case 0x6264 : if (position + HBIN_CELL_DB_SIZE < taille_fic)position = position + HBIN_CELL_DB_SIZE;else position++;break;//db
            default : position++; break;
          }
        }else if (((hb_ph->size[0]&0xFF) != 0x00) &&((hb_ph->size[1]&0xFF) == 0x00) && ((hb_ph->size[2]&0xFF) == 0x00) && ((hb_ph->size[3]&0xFF) == 0x00) && hb_ph->type == 0x6B6E)
        {
            position = position + Traiter_RegBin_nk_deleted(reg_file, position, taille_fic, buffer,session_id,db,TRUE);
        }else position++;
      }
    }
  }
  //on libère la mémoire
  HeapFree(GetProcessHeap(), 0, buffer);
}