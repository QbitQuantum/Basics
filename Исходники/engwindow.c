/*
 * @implemented
 */
BOOL
APIENTRY
WNDOBJ_bEnum(
  IN WNDOBJ  *pwo,
  IN ULONG  cj,
  OUT ULONG  *pul)
{
  WNDGDI *WndObjInt = ObjToGDI(pwo, WND);
  BOOL Ret;

  DPRINT("WNDOBJ_bEnum: pwo = 0x%p, cj = %lu, pul = 0x%p\n", pwo, cj, pul);
  Ret = CLIPOBJ_bEnum(WndObjInt->ClientClipObj, cj, pul);

  DPRINT("WNDOBJ_bEnum: Returning %s\n", Ret ? "True" : "False");
  return Ret;
}