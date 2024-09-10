/* Constructor of the object : it allocates memory and initializes the member
 * of the new object.
 * The user must give the initial GLYPHSET of the font or the master (which
 * may be NULL) in which case the character map will be empty.
 */
__GLCcharMap* __glcCharMapCreate(__GLCmaster* inMaster)
{
  __GLCcharMap* This = NULL;

  This = (__GLCcharMap*)__glcMalloc(sizeof(__GLCcharMap));
  if (!This) {
    __glcRaiseError(GLC_RESOURCE_ERROR);
    return NULL;
  }

  if (inMaster) {
    HFONT font;
    DWORD size;
    HDC dc = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);

    if (FAILED(dc)) {
      __glcFree(This);
      __glcRaiseError(GLC_RESOURCE_ERROR);
      return NULL;
    }
    font = CreateFontIndirect(&inMaster->pattern->elfLogFont);
    if (FAILED(font)) {
      DeleteDC(dc);
      __glcFree(This);
      __glcRaiseError(GLC_RESOURCE_ERROR);
      return NULL;
    }
    if (FAILED(SelectObject(dc, font))) {
      DeleteDC(dc);
      DeleteObject(font);
      __glcFree(This);
      __glcRaiseError(GLC_RESOURCE_ERROR);
      return NULL;
    }
    size = GetFontUnicodeRanges(dc, NULL);
    if (!size) {
      DeleteDC(dc);
      DeleteObject(font);
      __glcFree(This);
      __glcRaiseError(GLC_RESOURCE_ERROR);
      return NULL;
    }
    This->charSet = (LPGLYPHSET)__glcMalloc(size);
    if (!This->charSet) {
      DeleteDC(dc);
      DeleteObject(font);
      __glcRaiseError(GLC_RESOURCE_ERROR);
      __glcFree(This);
      return NULL;
    }
    if (!GetFontUnicodeRanges(dc, This->charSet)) {
      DeleteDC(dc);
      DeleteObject(font);
      __glcFree(This->charSet);
      __glcFree(This);
      __glcRaiseError(GLC_RESOURCE_ERROR);
      return NULL;
    }
    DeleteDC(dc);
    DeleteObject(font);
  }
  else {
    This->charSet = (LPGLYPHSET)__glcMalloc(sizeof(GLYPHSET));
    if (!This->charSet) {
      __glcRaiseError(GLC_RESOURCE_ERROR);
      __glcFree(This);
      return NULL;
    }
  }

  /* The array 'map' will contain the actual character map */
  This->map = __glcArrayCreate(sizeof(__GLCcharMapElement));
  if (!This->map) {
    __glcRaiseError(GLC_RESOURCE_ERROR);
    __glcFree(This->charSet);
    __glcFree(This);
    return NULL;
  }

  return This;
}