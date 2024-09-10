static HRESULT WINAPI IDirectMusicSegTriggerTrack_IPersistStream_Load (LPPERSISTSTREAM iface, IStream* pStm) {
  ICOM_THIS_MULTI(IDirectMusicSegTriggerTrack, PersistStreamVtbl, iface);

  DMUS_PRIVATE_CHUNK Chunk;
  LARGE_INTEGER liMove;
  HRESULT hr;

  TRACE("(%p, %p): Loading\n", This, pStm);
  
#if 1
  IStream_Read (pStm, &Chunk, sizeof(FOURCC)+sizeof(DWORD), NULL);
  TRACE_(dmfile)(": %s chunk (size = %d)", debugstr_fourcc (Chunk.fccID), Chunk.dwSize);
  switch (Chunk.fccID) {	
  case FOURCC_LIST: {
    IStream_Read (pStm, &Chunk.fccID, sizeof(FOURCC), NULL);
    TRACE_(dmfile)(": %s chunk (size = %d)", debugstr_fourcc (Chunk.fccID), Chunk.dwSize);
    switch (Chunk.fccID) {
    case DMUS_FOURCC_SEGTRACK_LIST: {
      TRACE_(dmfile)(": segment trigger track list\n");
      hr = IDirectMusicSegTriggerTrack_IPersistStream_ParseSegTrackList (iface, &Chunk, pStm);
      if (FAILED(hr)) return hr;
      break;    
    }
    default: {
      TRACE_(dmfile)(": unexpected chunk; loading failed)\n");
      liMove.QuadPart = Chunk.dwSize;
      IStream_Seek (pStm, liMove, STREAM_SEEK_CUR, NULL);
      return E_FAIL;
    }
    }
    TRACE_(dmfile)(": reading finished\n");
    break;
  }
  default: {
    TRACE_(dmfile)(": unexpected chunk; loading failed)\n");
    liMove.QuadPart = Chunk.dwSize;
    IStream_Seek (pStm, liMove, STREAM_SEEK_CUR, NULL); /* skip the rest of the chunk */
    return E_FAIL;
  }
  }  
#endif

  return S_OK;
}