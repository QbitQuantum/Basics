static JSValueRef beginDragWithFilesCallback(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    if (argumentCount < 1)
        return JSValueMakeUndefined(context);

    JSObjectRef filesArray = JSValueToObject(context, arguments[0], 0);

    if (!filesArray)
        return JSValueMakeUndefined(context);

    JSStringRef lengthProperty = JSStringCreateWithUTF8CString("length");
    Vector<UChar> files;
    int filesCount = JSValueToNumber(context, JSObjectGetProperty(context, filesArray, lengthProperty, 0), 0);
    for (int i = 0; i < filesCount; ++i) {
        JSValueRef value = JSObjectGetPropertyAtIndex(context, filesArray, i, 0);
        JSStringRef file = JSValueToStringCopy(context, value, 0);
        files.append(JSStringGetCharactersPtr(file), JSStringGetLength(file));
        files.append(0);
        JSStringRelease(file);
    }

    if (files.isEmpty())
        return JSValueMakeUndefined(context);

    // We should append "0" in the end of |files| so that |DragQueryFileW| retrieved the number of files correctly from Ole Clipboard.
    files.append(0);

    STGMEDIUM hDropMedium = {0};
    hDropMedium.tymed = TYMED_HGLOBAL;
    SIZE_T dropFilesSize = sizeof(DROPFILES) + (sizeof(WCHAR) * files.size());
    hDropMedium.hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, dropFilesSize);
    DROPFILES* dropFiles = reinterpret_cast<DROPFILES*>(GlobalLock(hDropMedium.hGlobal));
    memset(dropFiles, 0, sizeof(DROPFILES));
    dropFiles->pFiles = sizeof(DROPFILES);
    dropFiles->fWide = TRUE;

    UChar* data = reinterpret_cast<UChar*>(reinterpret_cast<BYTE*>(dropFiles) + sizeof(DROPFILES));
    for (size_t i = 0; i < files.size(); ++i)
        data[i] = files[i];
    GlobalUnlock(hDropMedium.hGlobal); 

    STGMEDIUM hFileNameMedium = {0};
    hFileNameMedium.tymed = TYMED_HGLOBAL;
    SIZE_T hFileNameSize = sizeof(WCHAR) * files.size();
    hFileNameMedium.hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, hFileNameSize);
    WCHAR* hFileName = static_cast<WCHAR*>(GlobalLock(hFileNameMedium.hGlobal));
    for (size_t i = 0; i < files.size(); i++)
        hFileName[i] = files[i];
    GlobalUnlock(hFileNameMedium.hGlobal);

    if (draggingInfo) {
        delete draggingInfo;
        draggingInfo = 0;
    }

    COMPtr<DRTDataObject> dataObeject;
    COMPtr<IDropSource> source;
    if (FAILED(DRTDataObject::createInstance(&dataObeject)))
        dataObeject = 0;

    if (FAILED(DRTDropSource::createInstance(&source)))
        source = 0;

    if (dataObeject && source) {
        draggingInfo = new DraggingInfo(dataObeject.get(), source.get());
        draggingInfo->setPerformedDropEffect(DROPEFFECT_COPY);
    }

    if (draggingInfo) {
        draggingInfo->dataObject()->SetData(cfHDropFormat(), &hDropMedium, FALSE);
        draggingInfo->dataObject()->SetData(cfFileNameWFormat(), &hFileNameMedium, FALSE);
        draggingInfo->dataObject()->SetData(cfUrlWFormat(), &hFileNameMedium, FALSE);
        OleSetClipboard(draggingInfo->dataObject());
        down = true;
    }

    JSStringRelease(lengthProperty);
    return JSValueMakeUndefined(context);
}