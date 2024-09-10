/**
 * @brief Begin a DnD operation.
 *
 * @param data The name pf the Drag operation.
 * @param size The size of the name.
 * @return @c EINA_TRUE on success, @c EINA_FALSE otherwise.
 *
 * This function start a Drag operation with the name @p data. If
 * @p data is @c NULL, @c EINA_FALSE is returned. if @p size is less than
 * @c 0, it is set to the length (as strlen()) of @p data. On success the
 * function returns @c EINA_TRUE, otherwise it returns @c EINA_FALSE.
 */
EAPI Eina_Bool
ecore_win32_dnd_begin(const char *data,
                      int         size)
{
   IDataObject *pDataObject = NULL;
   IDropSource *pDropSource = NULL;
   FORMATETC fmtetc = { CF_TEXT, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
   STGMEDIUM stgmed = { TYMED_HGLOBAL, { 0 }, 0 };
   Eina_Bool res = EINA_FALSE;

   if (!data)
      return EINA_FALSE;

   if (size < 0)
      size = strlen(data) + 1;

   stgmed.hGlobal = DataToHandle(data, size);

   // create the data object
   pDataObject = (IDataObject *)_ecore_win32_dnd_data_object_new((void *)&fmtetc,
                                                                 (void *)&stgmed,
                                                                 1);
   pDropSource = (IDropSource *)_ecore_win32_dnd_drop_source_new();

   if (pDataObject && pDropSource)
   {
      DWORD dwResult;
      DWORD dwEffect = DROPEFFECT_COPY;

      // do the drag-drop!
      dwResult = DoDragDrop(pDataObject, pDropSource, DROPEFFECT_COPY, &dwEffect);

      // finished. Check the return values to see if we need to do anything else
      if (dwResult == DRAGDROP_S_DROP)
      {
         //printf(">>> \"%s\" Dropped <<<\n", str);
         if(dwEffect == DROPEFFECT_MOVE)
         {
            // remove the data we just dropped from active document
         }
      }
      //else if (dwResult == DRAGDROP_S_CANCEL)
      //   printf("DND cancelled\n");
      //else
      //   printf("DND error\n");

      res = EINA_TRUE;
   }

   _ecore_win32_dnd_data_object_free(pDataObject);
   _ecore_win32_dnd_drop_source_free(pDropSource);

   // cleanup
   ReleaseStgMedium(&stgmed);

   return res;
}