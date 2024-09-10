static
PDH_STATUS
PdhiExpandCounterPath (
    IN      LPCWSTR szWildCardPath,
    IN      LPVOID  pExpandedPathList,
    IN      LPDWORD pcchPathListLength,
    IN      BOOL    bUnicode
)
{
    PPERF_MACHINE       pMachine;
    PPDHI_COUNTER_PATH  pWildCounterPath = NULL;
    WCHAR               szWorkBuffer[MAX_PATH];
    WCHAR               szCounterName[MAX_PATH];
    WCHAR               szInstanceName[MAX_PATH];
    LPWSTR              szEndOfObjectString;
    LPWSTR              szInstanceString;
    LPWSTR              szCounterString;
    LPVOID              szNextUserString;
    PERF_OBJECT_TYPE    *pObjectDef;
    PERF_OBJECT_TYPE    *pParentObjectDef;
    PERF_COUNTER_DEFINITION *pCounterDef;
    PERF_INSTANCE_DEFINITION *pInstanceDef;
    PERF_INSTANCE_DEFINITION *pParentInstanceDef;

    DWORD               dwBufferRemaining;
    DWORD               dwSize;
    DWORD               dwSizeReturned = 0;
    PDH_STATUS          pdhStatus = ERROR_SUCCESS;

    DWORD               dwCtrNdx, dwInstNdx;
    BOOL                bMoreData = FALSE;

    // allocate buffers
    pWildCounterPath = G_ALLOC (GPTR, PDHI_COUNTER_PATH_BUFFER_SIZE);

    if (pWildCounterPath == NULL) {
      // unable to allocate memory so bail out
      pdhStatus = PDH_MEMORY_ALLOCATION_FAILURE;
    } else {
      __try {
        dwBufferRemaining = *pcchPathListLength;
        szNextUserString = pExpandedPathList;
      } __except (EXCEPTION_EXECUTE_HANDLER) {
        pdhStatus = PDH_INVALID_ARGUMENT;
      }
    }

    if (pdhStatus == ERROR_SUCCESS) {
      // Parse wild card Path 
                  
      dwSize = G_SIZE (pWildCounterPath);
      if (ParseFullPathNameW (szWildCardPath, &dwSize, pWildCounterPath)) {
        // get the machine referenced in the path
        pMachine = GetMachine (pWildCounterPath->szMachineName, 0);
        if (pMachine != NULL) {
          if (wcsncmp (cszDoubleBackSlash, szWildCardPath, 2) == 0) {
            // the caller wants the machine name in the path so
            // copy it to the work buffer
            lstrcpyW (szWorkBuffer, pWildCounterPath->szMachineName);
          } else {
            *szWorkBuffer = 0;
          }
          // append the object name (since wild card objects are not
          // currently supported.

          lstrcatW (szWorkBuffer, cszBackSlash);
          lstrcatW (szWorkBuffer, pWildCounterPath->szObjectName);
          szEndOfObjectString = &szWorkBuffer[lstrlenW(szWorkBuffer)];
          
          // get object pointer (since objects are not wild)
          pObjectDef = GetObjectDefByName (
            pMachine->pSystemPerfData,
            pMachine->dwLastPerfString,
            pMachine->szPerfStrings,
            pWildCounterPath->szObjectName);

          if (pObjectDef != NULL) {
            // for each counters and identify matches
            pCounterDef = FirstCounter (pObjectDef);
            for (dwCtrNdx = 0; dwCtrNdx < pObjectDef->NumCounters; dwCtrNdx++) {
              // for each counter check instances (if supported) 
              //  and keep matches
              if ((pCounterDef->CounterNameTitleIndex > 0) &&
                  (pCounterDef->CounterNameTitleIndex < pMachine->dwLastPerfString ) &&
                  (!((pCounterDef->CounterType & PERF_DISPLAY_NOSHOW) &&
                     // this is a hack because this type is not defined correctly
                    (pCounterDef->CounterType != PERF_AVERAGE_BULK)))) {
                // look up name of each object & store size
                lstrcpyW (szCounterName,
                  pMachine->szPerfStrings[pCounterDef->CounterNameTitleIndex]);
                if (WildStringMatchW(pWildCounterPath->szCounterName, szCounterName)) {
                  // if this object has instances, then walk down
                  // the instance list and save any matches
                  if (pObjectDef->NumInstances != PERF_NO_INSTANCES) {
                    // then walk instances to find matches
                    pInstanceDef = FirstInstance (pObjectDef);
                    if (pObjectDef->NumInstances > 0) {
                      for (dwInstNdx = 0;
                        dwInstNdx < (DWORD)pObjectDef->NumInstances;
                        dwInstNdx++) {
                        szInstanceString = szEndOfObjectString;
                        if (pInstanceDef->ParentObjectTitleIndex > 0) {
                          // then add in parent instance name
                          pParentObjectDef = GetObjectDefByTitleIndex (
                            pMachine->pSystemPerfData,
                            pInstanceDef->ParentObjectTitleIndex);
                          if (pParentObjectDef != NULL) {
                            pParentInstanceDef = GetInstance (
                              pParentObjectDef,
                              pInstanceDef->ParentObjectInstance);
                            if (pParentInstanceDef != NULL) {
                              GetInstanceNameStr (pParentInstanceDef,
                                szInstanceName,
                                pObjectDef->CodePage);
                              if (WildStringMatchW (pWildCounterPath->szParentName, szInstanceName)) {
                                // add this string
                                szInstanceString = szEndOfObjectString;
                                lstrcpyW (szInstanceString, cszLeftParen);
                                lstrcatW (szInstanceString, szInstanceName);
                                lstrcatW (szInstanceString, cszSlash);
                              } else {
                                // get next instance and continue 
                                pInstanceDef = NextInstance(pInstanceDef);
                                continue;
                              }
                            } else {
                              // unable to locate parent instance
                              // so cancel this one, then 
                              // get next instance and continue 
                              pInstanceDef = NextInstance(pInstanceDef);
                              continue;
                            }
                          } else {
                            // unable to locate parent object
                            // so cancel this one, then 
                            // get next instance and continue 
                            pInstanceDef = NextInstance(pInstanceDef);
                            continue;
                          }
                        } else {
                          // no parent name so continue
                          szInstanceString = szEndOfObjectString;
                          lstrcpyW (szInstanceString, cszSlash);
                        }
                        GetInstanceNameStr (pInstanceDef,
                          szInstanceName,
                          pObjectDef->CodePage);

                        //
                        //  BUGBUG: need to do something with indexes.
                        //
                        // if this instance name matches, then keep it
                        if (WildStringMatchW (pWildCounterPath->szInstanceName, szInstanceName)) {
                          lstrcatW (szInstanceString, szInstanceName);
                          lstrcatW (szInstanceString, cszRightParenBackSlash);
                          // now append this counter name
                          lstrcatW (szInstanceString, szCounterName);

                          // add it to the user's buffer if there's room
                          dwSize = lstrlenW(szWorkBuffer) + 1;
                          if (!bMoreData && (dwSize  < dwBufferRemaining)) {
                            if (bUnicode) {
                                lstrcpyW ((LPWSTR)szNextUserString, szWorkBuffer);
                                (LPBYTE)szNextUserString += dwSize * sizeof(WCHAR);
                            } else {
                                wcstombs ((LPSTR)szNextUserString, szWorkBuffer, dwSize);
                                (LPBYTE)szNextUserString += dwSize * sizeof(CHAR);
                            }
                            dwSizeReturned += dwSize;
                            dwBufferRemaining -= dwSize;
                          } else {
                            // they've run out of buffer so just update the size required
                            bMoreData = TRUE;
                            dwSizeReturned += dwSize;
                          }
                        } else {
                          // they don't want this instance so skip it
                        }
                        pInstanceDef = NextInstance (pInstanceDef);
                      } // end for each instance in object
                    } else {
                      // this object supports instances, 
                      // but doesn't currently have any
                      // so do nothing.
                    }
                  } else {
                    // this object does not use instances so copy this
                    // counter to the caller's buffer.
                    szCounterString = szEndOfObjectString;
                    lstrcpyW (szCounterString, cszBackSlash);
                    lstrcatW (szCounterString, szCounterName);
                    dwSize = lstrlenW(szWorkBuffer) + 1;
                    if (!bMoreData && (dwSize  < dwBufferRemaining)) {
                      if (bUnicode) {
                        lstrcpyW ((LPWSTR)szNextUserString, szWorkBuffer);
                        (LPBYTE)szNextUserString += dwSize * sizeof(WCHAR);
                      } else {
                        wcstombs ((LPSTR)szNextUserString, szWorkBuffer, dwSize);
                        (LPBYTE)szNextUserString += dwSize * sizeof(CHAR);
                      }
                      dwSizeReturned += dwSize;
                      dwBufferRemaining -= dwSize;
                    } else {
                      // they've run out of buffer so bail out of this loop
                      bMoreData = TRUE;
                      dwSizeReturned += dwSize;
                    }
                  }
                } else {
                  // this counter doesn't match so skip it
                }
              } else {
                // this counter string is not available
              }
              pCounterDef = NextCounter(pCounterDef);
            } // end for each counter in this object
            if (bUnicode) {
                *(LPWSTR)szNextUserString = 0;  // MSZ terminator
            } else {
                *(LPSTR)szNextUserString = 0;  // MSZ terminator
            }
            *pcchPathListLength = dwSizeReturned;
            if (bMoreData) {
              pdhStatus = PDH_MORE_DATA;
            } else {
              pdhStatus = ERROR_SUCCESS;
            }
          } else {
            // unable to find object
            pdhStatus = PDH_INVALID_PATH;
          }
        } else {
          // unable to connect to machine.
          pdhStatus = PDH_CANNOT_CONNECT_MACHINE;
        }
      } else {
        // unable to read input path string
          pdhStatus = PDH_INVALID_PATH;
      }
    }

    if (pWildCounterPath != NULL) G_FREE (pWildCounterPath);

    return pdhStatus;
}