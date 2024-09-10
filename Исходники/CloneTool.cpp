//Performs the cloning
void CloneTool::clone(DibSection * ds, SHIFT shift)
{
	HDC dib_cdc=ds->GetCompDC();
	//PLSPEC: NT only
	MaskBlt(dib_cdc,maskOffset.x,maskOffset.y,usedSize.cx,usedSize.cy,
		dib_cdc,maskOffset.x+shift.x,maskOffset.y+shift.y,
		mask->GetDSHandle(),0,0,
		MAKEROP4(ROP3_NOP,SRCCOPY));
}