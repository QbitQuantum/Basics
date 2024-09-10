int 
TCommCtrlDll::LBItemFromPt(HWND hLB, POINT pt, bool bAutoScroll)
{
  static TModuleProc3<int,HWND,POINT,BOOL> lBItemFromPt(GetModule(), LBItemFromPtStr);
  return lBItemFromPt(hLB, pt, bAutoScroll);
}