   bool Create(const TCHAR* file)
   {
      USES_CONVERSION;
      int array_count = GetFieldCount();
      DBaseFieldVector vector;

      vector.resize(array_count);
	  for (int i = 0; i < array_count; i++)
      {
         CDaoFieldInfo info;
         DBF_FIELD_INFO* item = &vector[i];
	  
         GetFieldInfo(i, info);
         strncpy(item->name, T2CA(info.m_strName), _countof(item->name));
         item->name[_countof(item->name) - 1] = 0;
         item->decimals = 0;
         item->length = info.m_lSize;
         item->type = GetFieldType(i, info, &item->length);
      }

      zlib_filefunc_def api;
      fill_fopen_filefunc(&api);
      void* stream = api.zopen_file(api.opaque, T2CA(file), ZLIB_FILEFUNC_MODE_CREATE | ZLIB_FILEFUNC_MODE_WRITE);
      bool ok = (NULL != stream);

      if (ok)
         ok = m_dbf.Create(file, stream, &api, vector);
      return ok;
   }