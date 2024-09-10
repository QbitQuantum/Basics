__declspec(dllexport) void  GetCurrentTopology(DISPLAYCONFIG_TOPOLOGY_ID *peCurrentTopology) {

      // Get the current topology - make sure that we aren't resetting the topology to the same that it
      // currently is - otherwise it can cause unnecessary flashing on the screen.
      LONG result;
      UINT32 NumPathArrayElements;
      UINT32 NumModeInfoArrayElements;
      DISPLAYCONFIG_PATH_INFO *pPathInfoArray;
      DISPLAYCONFIG_MODE_INFO *pModeInfoArray;
      result = GetDisplayConfigBufferSizes(QDC_DATABASE_CURRENT, &NumPathArrayElements, &NumModeInfoArrayElements);

      if (result != ERROR_SUCCESS)
            return;

      if (peCurrentTopology == NULL)
            return;

      // The only reason to allocate these structures is that the documentation says that QueryDisplayConfig
      // cannot take null for the pPathInfoArray and pModeInfoArray  elements.  I have tried to have static
      // structures that get passed in with only one element and have had things fail in the past
      // The only way that I've gotten this interface to reliably work is to call GetDisplayConfigBufferSizes
      // and then allocate AND ZERO the structures that are passed in.  This interface is incredibly
      // fragile and you are going to want to do everything that it expects, or it will return
      // "invalid parameter"
      pPathInfoArray = (DISPLAYCONFIG_PATH_INFO *)malloc(NumPathArrayElements * sizeof(DISPLAYCONFIG_PATH_INFO));
      if (!pPathInfoArray)
            return;
      pModeInfoArray = (DISPLAYCONFIG_MODE_INFO *)malloc(NumModeInfoArrayElements * sizeof(DISPLAYCONFIG_MODE_INFO));
      if (!pModeInfoArray)
      {
            if (pPathInfoArray)
                  free(pPathInfoArray);
            return;
      }
      memset(pPathInfoArray, 0, NumPathArrayElements * sizeof(DISPLAYCONFIG_PATH_INFO));
      memset(pModeInfoArray, 0, NumModeInfoArrayElements * sizeof(DISPLAYCONFIG_MODE_INFO));

      result = QueryDisplayConfig(QDC_DATABASE_CURRENT,
                                                &NumPathArrayElements,
                                                pPathInfoArray,
                                                &NumModeInfoArrayElements,
                                                pModeInfoArray,
                                                peCurrentTopology);

      // Free the structures, don't care what is in them
      free(pPathInfoArray);
      free(pModeInfoArray);
      if (result != ERROR_SUCCESS)
            return;
      return;
}