int _tmain(int argc, _TCHAR* argv[])
{
  HANDLE rar_handle = NULL;
  //std::wstring fn_rar = L"E:\\-=eMule=-\\1140746814_39741.rar";
  //std::wstring fn_rar = L"E:\\-=eMule=-\\Bride.Flight.2008.Bluray.720p.AC3.x264-CHD_ÐÂÄïº½°à\\B2_ÐÂÄïº½°à.part1.rar";
  //std::wstring fn_rar = L"D:\\xxxx.part1.rar";
  std::wstring fn_rar = L"E:\\-=eMule=-\\Overheard.2009.REPACK.CN.DVDRip.Xvid-XTM\\sample\\xtm-overheard.repack-sample_stored.rar";
  //std::wstring fn_rar = L"E:\\-=eMule=-\\Overheard.2009.REPACK.CN.DVDRip.Xvid-XTM\\sample\\xtm-overheard.repack-sample_s.part1.rar";
  
  std::wstring tmp_dir = L"C:\\Temp\\";
  
  struct RAROpenArchiveDataEx ArchiveDataEx;
  memset(&ArchiveDataEx, 0, sizeof(ArchiveDataEx));
  
  ArchiveDataEx.ArcNameW = (wchar_t*)fn_rar.c_str();
  //ArchiveDataEx.ArcName = "E:\\-=eMule=-\\1140746814_39741.rar";

  ArchiveDataEx.OpenMode = RAR_OM_EXTRACT;
  ArchiveDataEx.CmtBuf = 0;
  rar_handle = RAROpenArchiveEx(&ArchiveDataEx);

  const long buffsize = 1000;
  char testbuff[buffsize];

  if (rar_handle)
  {
    wprintf(L"RAROpenArchiveEx open successed\n");
    struct RARHeaderDataEx HeaderDataEx;
    HeaderDataEx.CmtBuf = NULL;
    while (RARReadHeaderEx(rar_handle, &HeaderDataEx) == 0)
    {
      // Õý³£½âÑ¹¸ÃÎÄ¼þ
      unsigned long long filesize = ((unsigned long long)HeaderDataEx.UnpSizeHigh << 32) + HeaderDataEx.UnpSize;
      int err = 0;
      std::wstring unp_tmpfile = tmp_dir + HeaderDataEx.FileNameW;
      err = RARProcessFileW(rar_handle, RAR_EXTRACT, (wchar_t*)tmp_dir.c_str(), HeaderDataEx.FileNameW);
      wprintf(L"RARProcessFileW to %s return %d size %lld %x %x\n", unp_tmpfile.c_str(), err, filesize, HeaderDataEx.UnpVer, HeaderDataEx.Method);
    }
    RARCloseArchive(rar_handle);
  }

  rar_handle = RAROpenArchiveEx(&ArchiveDataEx);
  if (rar_handle)
  {
    wprintf(L"RAROpenArchiveEx open successed\n");
    struct RARHeaderDataEx HeaderDataEx;
    HeaderDataEx.CmtBuf = NULL;
    while (RARReadHeaderEx(rar_handle, &HeaderDataEx) == 0)
    {
      unsigned long long filesize = ((unsigned long long)HeaderDataEx.UnpSizeHigh << 32) + HeaderDataEx.UnpSize;
      int err = 0;
      std::wstring unp_tmpfile = tmp_dir + HeaderDataEx.FileNameW;
      err = RARExtractChunkInit(rar_handle, HeaderDataEx.FileName);
      if (err != 0)
      {
        wprintf(L"RARExtractChunkInit return error %d\n", err);
        continue;
      }

      FILE* unp_filehandle = NULL;
      err = _wfopen_s(&unp_filehandle, unp_tmpfile.c_str(), L"rb");
      if (err)
      {
        wprintf(L"open extracted file fail %d %d\n", err, unp_filehandle);
        continue;
      }

      
      // Ë³Ðò²âÊÔ
      int iExtractRet = 0;
      unsigned long long fpos = 0;
      do
      {
        iExtractRet = RARExtractChunk(rar_handle, (char*)testbuff, buffsize);
        // Compare 
        if (compare_filebinary(unp_filehandle, fpos, testbuff, iExtractRet, 0))
        {
          wprintf(L"Sequence compare difference found at %lld for %d\n", fpos, buffsize);
          break;
        }
        //else
        //  wprintf(L"Sequence compare is same %lld %d\n", fpos, iExtractRet);

        fpos += iExtractRet;
      } while(iExtractRet > 0);

      // Ëæ»ú²âÊÔ
      for (int i = 0; i < 100; i++)
      {
        unsigned long long ll_pos = rand() * filesize/RAND_MAX;
        RARExtractChunkSeek(rar_handle, ll_pos, SEEK_SET);
        RARExtractChunk(rar_handle, (char*)testbuff, buffsize);
        // Compare 
        if (compare_filebinary(unp_filehandle, ll_pos, testbuff, iExtractRet, 0))
        {
          wprintf(L"Random compare difference found at %lld\n", ll_pos);
          break;
        }
        //else
        //  wprintf(L"Random compare is same %lld\n", ll_pos);
      }
      wprintf(L"RARExtractChunk test for %s finished\n", unp_tmpfile.c_str());
    }
    RARCloseArchive(rar_handle);
  }
  wprintf(L"Test finished\n");
  scanf_s("%d");
	return 0;
}