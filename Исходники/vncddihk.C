BOOL RectToAdd()
{
	RECT rect;
	BOOL result; 
	if (region==NULL) return 1;
	rect.left=left;
	rect.top=top;
	rect.right=right;
	rect.bottom=bottom;
	result= RectInRegion(region,&rect);
	return (result);
}