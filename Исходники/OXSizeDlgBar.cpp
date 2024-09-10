// deletes the underlying array and it's elements
void DestroyGadgetResizeHandle(GADGETRESIZEHANDLE Handle)
	{
	CPtrArray* pArray = (CPtrArray*)Handle;		
	if (pArray != NULL)
		{
		for (int i = PtrToInt(pArray->GetUpperBound()); i >= 0; i--)
			delete ((RECT_AND_HWND*)pArray->GetAt(i));
		delete pArray;
		}
	}