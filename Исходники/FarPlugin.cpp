int WINAPI _export GetArcItem(struct PluginPanelItem *Item,struct ArcItemInfo *Info)
{
  if (setjmp(jumper) != 0)
    {cleanup(); return GETARC_BROKEN;}  // Сюда мы попадём при возникновении ошибки в одной из вызываемых процедур

  // Считаем следующий блок каталога архива, если все файлы из текущего уже перечислены
  if( current_block < 0 || ++current_file_in_block >= dirblock->total_files)
  {
    FreeAndNil (dirblock);
    for(;;)
    {
      if( ++current_block == arcinfo->control_blocks_descriptors.size )
      {
        return GETARC_EOF;
      }

      // Если это блок каталога - прочитаем его и выйдем из цикла
      BLOCK& descriptor = arcinfo->control_blocks_descriptors [current_block];
      if (descriptor.type == DIR_BLOCK)
      {
         dirblock = new DIRECTORY_BLOCK (*arcinfo, descriptor);
         current_file_in_block = current_data_block = 0;
         if (dirblock->total_files>0)  break;
         FreeAndNil (dirblock);
      }
    }
    //printf("%d files\n", dirblock->total_files);
  }

  // Заполним описание файла
  int i = current_file_in_block;
  Item->FindData.dwFileAttributes = dirblock->isdir[i]? FILE_ATTRIBUTE_DIRECTORY : 0;
  UnixTimeToFileTime (dirblock->time[i], &Item->FindData.ftLastWriteTime);
  Item->FindData.nFileSizeHigh = ((uint64) dirblock->size[i]) >> 32;
  Item->FindData.nFileSizeLow  = dirblock->size[i];
  char utf8name[MY_FILENAME_MAX*4]; WCHAR utf16name[MY_FILENAME_MAX*2];
  dirblock->fullname (i, utf8name);
  utf8_to_utf16 (utf8name, utf16name);
  CharToOemW (utf16name, Item->FindData.cFileName);
  Item->CRC32  = dirblock->crc[i];
  Info->UnpVer = UnpVer;

  // Теперь извлечём информацию из описания солид-блока
  int &b = current_data_block;
  // Увеличим номер солид-блока если мы вышли за последний принадлежащий ему файл
  if (current_file_in_block >= dirblock->block_end(b))
    b++;
  // Если это первый файл в солид-блоке - соберём block-related информацию
  if (current_file_in_block == dirblock->block_start(b))
  { // Запишем на первый файл в блоке весь его упакованный размер
    uint64 packed = dirblock->data_block[b].compsize;
    Item->PackSizeHigh = packed >> 32;
    Item->PackSize     = packed;
    // Запомним информацию о солид-блоке для использования её со всеми файлами из этого солид-блока
    char *c = dirblock->data_block[b].compressor;
    Solid     = dirblock->block_start(b)+1 != dirblock->block_end(b);
    Encrypted = strstr (c, "+aes-")!=NULL || strstr (c, "+serpent-")!=NULL || strstr (c, "+blowfish-")!=NULL || strstr (c, "+twofish-")!=NULL;
    DictSize  = compressorGetDecompressionMem (dirblock->data_block[b].compressor);
  }