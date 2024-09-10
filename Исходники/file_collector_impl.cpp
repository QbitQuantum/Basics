bool_t FileCollectorImpl::searchAllFile(collector_log_type_e collector_log_type
                                        ,CollectRule* pCollectRule, file_collect_callback_t pfn_cb, void* context) {

  ASSERT(pCollectRule);
  ASSERT(pfn_cb);

  // now
  struct tm today;
  time_t now = time(NULL);
  LOCALTIME(today, now);

  WIN32_FIND_DATA find_file_data;

  //__try 
  {

    HANDLE find_handle = FindFirstFile(pCollectRule->find_dir, &find_file_data);

    if (find_handle != INVALID_HANDLE_VALUE) {
      do {
        // Don't count current or parent directories.
        if ((STRCMP(find_file_data.cFileName, _STR("..")) == 0) ||
          (STRCMP(find_file_data.cFileName, _STR(".")) == 0))
          continue;

        if (find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { continue; }

        /*
        long result = CompareFileTime(&find_file_data.ftCreationTime,  // NOLINT
          &comparison_filetime);
        // File was created after or on comparison time
        if ((result == 1) || (result == 0))
          ++file_count;
        */

        // is we need file
        //uint32_t nMatchLen = STRLEN(find_file_data.cFileName);
        if (TRUE == pCollectRule->regExExclude.didCompile()
          && TRUE == pCollectRule->regExExclude.isMatchOnly(find_file_data.cFileName)
        ) { continue; }

        if (FALSE == pCollectRule->regExInclude.isMatchOnly(find_file_data.cFileName)) { continue; }

        // test file
//         char_t strPath[MAX_PATH + 1] = {0};
//         SNPRINTF(strPath, MAX_PATH, MAX_PATH, "%s/%s", pCollectRule->dir, find_file_data.cFileName);
//         AutoReleaseFile autoRelFile(OpenFile(strPath, strAttrOpenRead));
//         if (NULL == autoRelFile) { continue; }

        // find map
        FileNode* pFileNode;
        if (MEM_NINI_LOG == collector_log_type) {
          pFileNode = findFileNode(pCollectRule->mml_hash, find_file_data.cFileName);
        }
        else {
          pFileNode = findFileNode(pCollectRule->hash, find_file_data.cFileName);
        }
        if (NULL == pFileNode) {

          if (TRUE == m_bAfterToDay) {
          // time control
          SYSTEMTIME nCreateTime;
          SYSTEMTIME stUTC;
          if (FALSE == FileTimeToSystemTime(&(find_file_data.ftCreationTime), &stUTC)
            || FALSE == SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &nCreateTime)
            ) { continue; }

          if (nCreateTime.wYear != today.tm_year + 1900
            || nCreateTime.wMonth != today.tm_mon + 1
            || nCreateTime.wDay != today.tm_mday
            ) { continue; }
          }


//           char_t strPath[MAX_PATH + 1] = {0};
//           SNPRINTF(strPath, MAX_PATH, MAX_PATH, "%s/%s", pCollectRule->dir, find_file_data.cFileName);

//           AutoReleaseFile AutoRelFile(::OpenFile(strPath, strAttrOpenRead));
//           if (NULL == AutoRelFile) { continue; }
// 
          pFileNode = new FileNode(pCollectRule->dir
            , MEM_NINI_LOG == collector_log_type ? pCollectRule->GetMMLDir() : NULL
            , find_file_data.cFileName);
          if (NULL == pFileNode) { continue; }

          // update file info
          FindData2FileInfo(&pFileNode->FileInfo(), find_file_data);

          // add to map
          addFileNode(pCollectRule->hash, pFileNode->LocalName(), pFileNode);

          // new file
          if (RC_S_OK != (pfn_cb)(/*this, */pFileNode, context)) { break; }
        }
        else {

          ASSERT(pFileNode);

          // update file info
          PlatformFileInfo& fileInfo = pFileNode->FileInfo();
          FindData2FileInfo(&fileInfo, find_file_data);

          if (pFileNode->GetSendSize() < fileInfo.size) {

            // new data
            if (RC_S_OK != (pfn_cb)(/*this, */pFileNode, context)) { break; }
          }
        }

      } while (FindNextFile(find_handle,  &find_file_data));

      FindClose(find_handle);
    }
  }
//    __except(EXCEPTION_EXECUTE_HANDLER) {
// 
//     return TRUE;
//   }

  return TRUE;
}