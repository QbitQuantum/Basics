DECLSPEC_HIDDEN HRESULT WINAPI fnTextSrv_TxSetText(ITextServices *iface, LPCWSTR pszText)
{
   ITextServicesImpl *This = impl_from_ITextServices(iface);
   ME_Cursor cursor;

   ME_SetCursorToStart(This->editor, &cursor);
   ME_InternalDeleteText(This->editor, &cursor,
                         ME_GetTextLength(This->editor), FALSE);
   ME_InsertTextFromCursor(This->editor, 0, pszText, -1,
                           This->editor->pBuffer->pDefaultStyle);
   ME_SetSelection(This->editor, 0, 0);
   This->editor->nModifyStep = 0;
   OleFlushClipboard();
   ME_EmptyUndoStack(This->editor);
   ME_UpdateRepaint(This->editor, FALSE);

   return S_OK;
}