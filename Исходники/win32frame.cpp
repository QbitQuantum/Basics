//------------------------------------------------------------------------------------
CView::DragResult Win32Frame::doDrag (IDataPackage* source, const CPoint& offset, CBitmap* dragBitmap)
{
	CView::DragResult result = CView::kDragRefused;
	Win32DataObject* dataObject = new Win32DataObject (source);
	Win32DropSource* dropSource = new Win32DropSource;
	DWORD outEffect;
	HRESULT hResult = DoDragDrop (dataObject, dropSource, DROPEFFECT_COPY, &outEffect);
	dataObject->Release ();
	dropSource->Release ();
	if (hResult == DRAGDROP_S_DROP)
	{
		if (outEffect == DROPEFFECT_MOVE)
			result = CView::kDragMoved;
		else
			result = CView::kDragCopied;
	}
	return result;
}