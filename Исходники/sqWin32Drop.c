void SetupDragAndDrop(void) {
  HRESULT hRes;
#if 0
  return;
#endif
  if(!isInitialized) {
    stDropTarget.vtbl = vtDropTarget;
    stDropTarget.ref = 0;
    isInitialized = 1;
  }
  hRes = RegisterDragDrop(stWindow, (LPDROPTARGET)&stDropTarget);
  if(hRes == S_OK) {
    DPRINTF(("Registered drop target\n"));
  } else {
    DPRINTF(("Drop registration failed (errCode: %x)\n", hRes));
  }
}