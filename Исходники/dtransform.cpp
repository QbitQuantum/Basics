BOOL DTransformRotation::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
//	return DTransformScale::OnSetActive();
	GView *view = GetView();

	// make translation event handler active 
	GMoveTransformHandler *h = new GMoveTransformHandler(view);
	h->SetMapMode(m_type);
	h->SetTransformMode(GMoveTransformHandler::MODE_ROTATE);
	h->SetDialog(this);
	h->SetAxes(GetAxes());
	h->rotateTrackball = m_trackball;
	h->ref();

	m_pView->Message("Select and drag scales object"); 

	m_handler = h;
    view->PushEventHandler(h);

	
	return CPropertyPage::OnSetActive();

}