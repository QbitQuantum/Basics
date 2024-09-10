BOOL CDiagramEntity::BodyInRect( CRect rect ) const
/* ============================================================
	Function :		CDiagramEntity::BodyInRect
	Description :	Used to see if any part of the object lies 
					in rect.
					
	Return :		BOOL		-	TRUE if any part of the 
									object lies inside rect.
	Parameters :	CRect rect	-	The rect to check.
					
	Usage :			Call to see if the object overlaps - for 
					example - a selection rubberband.

   ============================================================*/
{

	BOOL result = FALSE;
	CRect rectEntity = GetRect();
	CRect rectIntersect;

	rect.NormalizeRect();
	rectEntity.NormalizeRect();

	rectIntersect.IntersectRect( rect, rectEntity );
	if( !rectIntersect.IsRectEmpty() )
		result = TRUE;

	return result;

}