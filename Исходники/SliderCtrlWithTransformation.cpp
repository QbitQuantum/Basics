void CSliderCtrlWithTransformation::substituteControl(CWnd *parent, int id, DoubleInterval &interval, UINT steps, IntervalScale type) {
  DEFINEMETHODNAME;
  CSliderCtrl *ctrl = (CSliderCtrl*)parent->GetDlgItem(id);
  if(ctrl == NULL) {
    showError(_T("%s:Control %d not found"), method, id);
    return;
  }
  const int   style   = ctrl->GetStyle();
  const int   exStyle = ctrl->GetExStyle();
  const CRect rect    = getWindowRect(ctrl);
  ctrl->DestroyWindow();
  if(!Create(style, rect, parent, id)) {
    showError(_T("%s:Create failed"), method);
    return;
  }
  ModifyStyleEx(0, exStyle);
  setTransformation(interval, steps, type);
}