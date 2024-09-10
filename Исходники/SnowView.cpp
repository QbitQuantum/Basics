void SnowView::AttachedToWindow()
{
	BView *p;
	rgb_color col;
	fAttached = true;
/*	if (!fMsgRunner)
		fMsgRunner = new BMessageRunner(BMessenger(this), 
					new BMessage(MSG_PULSE_ME), 
					INTERVAL);
*/
	p = Parent();
	if (p)
		col = B_TRANSPARENT_32_BIT;//Parent()->ViewColor();
	else
		col = ui_color(B_PANEL_BACKGROUND_COLOR);
	SetViewColor(col);
//	BScreen bs;
//	fCachedWsWidth = bs.Frame().IntegerWidth();
//	fCachedWsHeight = bs.Frame().IntegerHeight();
	fDragger = dynamic_cast<BDragger *>(FindView("_dragger_"));
	if (fDragger && p) {
		fCachedParent = p;
		fCachedWsWidth = p->Frame().IntegerWidth();
		fCachedWsHeight = p->Frame().IntegerHeight();
		fDragger->SetViewColor(col);
		if (fDragger->InShelf()) {
			p->SetFlags(p->Flags() | B_DRAW_ON_CHILDREN);
#ifdef B_BEOS_VERSION_DANO
			p->SetDoubleBuffering(p->DoubleBuffering() | B_UPDATE_EXPOSED);
#endif
			ResizeTo(p->Bounds().Width(), p->Bounds().Height());
			MoveTo(0,0);
			fDragger->MoveTo(p->Bounds().Width()-7, p->Bounds().Height()-7);
		}
		BRect fallenRect(p->Bounds());
		fallenRect.top = fallenRect.bottom - FALLEN_HEIGHT;
		fFallenBmp = new BBitmap(fallenRect, B_BITMAP_ACCEPTS_VIEWS, B_CMAP8);
		memset(fFallenBmp->Bits(), B_TRANSPARENT_MAGIC_CMAP8, (size_t)(fallenRect.Height()*fFallenBmp->BytesPerRow()));
		fFallenView = new BView(fallenRect, "offscreen fallen snow", B_FOLLOW_NONE, 0);
		fFallenBmp->AddChild(fFallenView);
		fFallenReg = new BRegion;
		fInvalidator = spawn_thread(SnowMakerThread, INVALIDATOR_THREAD_NAME, B_LOW_PRIORITY, (void *)this);
		resume_thread(fInvalidator);
		printf("BSnow: OK: ws = %ld x %ld\n", fCachedWsWidth, fCachedWsHeight);
#ifdef DEBUG
		Window()->AddCommonFilter(new BMessageFilter(B_ANY_DELIVERY, B_ANY_SOURCE, msgfilter));
#endif
	}
}