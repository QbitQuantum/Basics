void MediaJack::_updateBitmap()
{
	D_METHOD(("MediaJack::_updateBitmap()\n"));

	if (m_bitmap)
	{
		delete m_bitmap;
	}
	BBitmap *tempBitmap = new BBitmap(Frame().OffsetToCopy(0.0, 0.0), B_CMAP8, true);
	tempBitmap->Lock();
	{
		BView *tempView = new BView(tempBitmap->Bounds(), "", B_FOLLOW_NONE, 0);
		tempBitmap->AddChild(tempView);
		tempView->SetOrigin(0.0, 0.0);

		MediaRoutingView* mediaView = dynamic_cast<MediaRoutingView*>(view());
		int32 layout = mediaView ? mediaView->getLayout() : MediaRoutingView::M_ICON_VIEW;

		_drawInto(tempView, tempView->Bounds(), layout);

		tempView->Sync();
		tempBitmap->RemoveChild(tempView);
		delete tempView;
	}
	tempBitmap->Unlock();
	m_bitmap = new BBitmap(tempBitmap);
	delete tempBitmap;
}