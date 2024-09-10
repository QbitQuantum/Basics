BOOL WINAPI
SubtractRect( LPRECT dest, const RECT *src1, const RECT *src2 )
{
    RECT tmp;

    if (IsRectEmpty( src1 ))
    {
	SetRectEmpty( dest );
	return FALSE;
    }
    *dest = *src1;
    if (IntersectRect( &tmp, src1, src2 ))
    {
	if (EqualRect( &tmp, dest ))
	{
	    SetRectEmpty( dest );
	    return FALSE;
	}
	if ((tmp.top == dest->top) && (tmp.bottom == dest->bottom))
	{
	    if (tmp.left == dest->left) dest->left = tmp.right;
	    else if (tmp.right == dest->right) dest->right = tmp.left;
	}
	else if ((tmp.left == dest->left) && (tmp.right == dest->right))
	{
	    if (tmp.top == dest->top) dest->top = tmp.bottom;
	    else if (tmp.bottom == dest->bottom) dest->bottom = tmp.top;
	}
    }
    return TRUE;
}