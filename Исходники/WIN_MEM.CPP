//////////////////////////
// Deallocate your memory
//////////////////////////
void Dealloc(VOIDPTR pMem)
{
  HANDLE hMem;

  ///////////////////////////////
  // Memory debugging code
  ///////////////////////////////

  if (pMem != NULL)
  {
    hMem = GlobalHandle(SELECTOROF(pMem));

    if (hMem != NULL)
    {
      GlobalUnlock(hMem);
      GlobalFree(hMem);

      pMem = NULL;
    }
  }
}