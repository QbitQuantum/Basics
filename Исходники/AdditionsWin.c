void
UpdateAdditionsWin(void)
{
	Rect		r;
	Cell		c;
	int			i;
	GrafPtr		oldPort;
	GetPort(&oldPort);
	
	SetPort(gWPtr);
	
	MoveTo( gControls->aw->compListBox.left, gControls->aw->compListBox.top - kInterWidgetPad + 1);
	HLock(gControls->cfg->selAddMsg);
	DrawString( CToPascal(*gControls->cfg->selAddMsg));
	HUnlock(gControls->cfg->selAddMsg);
	
#if 0
	RGBColor backColorOld;
    Rect adjustedRect, *clRect = &gControls->aw->compListBox;
    SetRect(&adjustedRect, clRect->left, clRect->top+1, clRect->right, clRect->bottom-1);
    GetBackColor(&backColorOld);
    BackColor(whiteColor);
    EraseRect(&adjustedRect);
    RGBBackColor(&backColorOld);
#endif
   
	LUpdate( (*gControls->aw->compList)->port->visRgn, gControls->aw->compList);
	SetRect(&r, gControls->aw->compListBox.left, gControls->aw->compListBox.top,
	            gControls->aw->compListBox.right + 1, gControls->aw->compListBox.bottom);
	FrameRect(&r);	
	
	SetPt(&c, 0, 0);
	if (LGetSelect(true, &c, gControls->aw->compList))
	{
		HLock((Handle)gControls->aw->compDescTxt);
		SetRect(&r, (*gControls->aw->compDescTxt)->viewRect.left,
					(*gControls->aw->compDescTxt)->viewRect.top,
					(*gControls->aw->compDescTxt)->viewRect.right,
					(*gControls->aw->compDescTxt)->viewRect.bottom);
		HUnlock((Handle)gControls->aw->compDescTxt);
		TEUpdate(&r, gControls->aw->compDescTxt);	
	}
	
	DrawDiskSpaceMsgs( gControls->opt->vRefNum );
	
	for (i = 0; i < numRows; i++)
	{
		if (gControls->cfg->comp[rowToComp[i]].highlighted)
		{
			AddInitRowHighlight(i);
			break;
		}
	}
	
	SetPort(oldPort);
}