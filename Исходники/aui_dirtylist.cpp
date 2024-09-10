AUI_ERRCODE aui_DirtyList::SubtractRect(
	sint32 left,
	sint32 top,
	sint32 right,
	sint32 bottom )
{
	RECT rect = { left, top, right, bottom };
	return SubtractRect( &rect );
}