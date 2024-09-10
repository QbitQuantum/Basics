void WebDragClient::startDrag(DragImageRef image, const IntPoint& imageOrigin, const IntPoint& dragPoint, Clipboard* clipboard, Frame* frame, bool isLink)
{
    //FIXME: Allow UIDelegate to override behaviour <rdar://problem/5015953>

    //We liberally protect everything, to protect against a load occurring mid-drag
    RefPtr<Frame> frameProtector = frame;
    COMPtr<IDragSourceHelper> helper;
    COMPtr<IDataObject> dataObject;
    COMPtr<WebView> viewProtector = m_webView;
    COMPtr<IDropSource> source;
    if (FAILED(WebDropSource::createInstance(m_webView, &source)))
        return;

    dataObject = static_cast<ClipboardWin*>(clipboard)->dataObject();
    if (source && (image || dataObject)) {
        if (image) {
            if(SUCCEEDED(CoCreateInstance(CLSID_DragDropHelper, 0, CLSCTX_INPROC_SERVER,
                IID_IDragSourceHelper,(LPVOID*)&helper))) {
                BITMAP b;
                GetObject(image, sizeof(BITMAP), &b);
                SHDRAGIMAGE sdi;
                sdi.sizeDragImage.cx = b.bmWidth;
                sdi.sizeDragImage.cy = b.bmHeight;
                sdi.crColorKey = 0xffffffff;
                sdi.hbmpDragImage = image;
                sdi.ptOffset.x = dragPoint.x() - imageOrigin.x();
                sdi.ptOffset.y = dragPoint.y() - imageOrigin.y();
                if (isLink)
                    sdi.ptOffset.y = b.bmHeight - sdi.ptOffset.y;

                helper->InitializeFromBitmap(&sdi, dataObject.get());
            }
        }

        //FIXME: Ensure correct drag ops are available <rdar://problem/5015957>
        DWORD okEffect = DROPEFFECT_COPY | DROPEFFECT_LINK | DROPEFFECT_MOVE;
        DWORD effect;
        COMPtr<IWebUIDelegate> ui;
        if (SUCCEEDED(m_webView->uiDelegate(&ui))) {
            COMPtr<IWebUIDelegatePrivate> uiPrivate;
            if (SUCCEEDED(ui->QueryInterface(IID_IWebUIDelegatePrivate, (void**)&uiPrivate)))
                if (SUCCEEDED(uiPrivate->doDragDrop(m_webView, dataObject.get(), source.get(), okEffect, &effect)))
                    return;
        }

        DoDragDrop(dataObject.get(), source.get(), okEffect, &effect);
    }
}