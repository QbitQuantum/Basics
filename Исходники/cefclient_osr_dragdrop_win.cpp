CefBrowserHost::DragOperationsMask DropTargetWin::StartDragging(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefDragData> drag_data,
	void* hbitmap,
	int imgcx,
	int imgcy,
	int imgx,
	int imgy,
    CefRenderHandler::DragOperationsMask allowed_ops,
    int x, int y) {
  CComPtr<IDataObject> dataObject;
  DWORD resEffect = DROPEFFECT_NONE;
  if (DragDataToDataObject(drag_data, &dataObject)) {
	  IDragSourceHelper* sourceHelper = DragHelper();
	HRESULT hr;
	if (sourceHelper)
	{
		SHDRAGIMAGE sdi;
		SIZE img_size{ imgcx, imgcy };
		sdi.sizeDragImage = img_size;
		sdi.crColorKey = 0xFFFFFFFF;
		sdi.hbmpDragImage = (HBITMAP)hbitmap;
		POINT img_pt{imgx, imgy};
		sdi.ptOffset = img_pt;
		hr = sourceHelper->InitializeFromBitmap(&sdi, dataObject);
	}
    CComPtr<IDropSource> dropSource = DropSourceWin::Create();
    DWORD effect = DragOperationToDropEffect(allowed_ops);
    current_drag_data_ = drag_data->Clone();
    current_drag_data_->ResetFileContents();
    HRESULT res = DoDragDrop(dataObject, dropSource, effect, &resEffect);
    if (res != DRAGDROP_S_DROP)
      resEffect = DROPEFFECT_NONE;
    current_drag_data_ = NULL;
  }
  return DropEffectToDragOperation(resEffect);
}