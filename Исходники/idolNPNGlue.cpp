void NPN_InvalidateRect(NPP instance, NPRect *invalidRect)
{
  NPNFuncs.invalidaterect(instance, invalidRect);
}