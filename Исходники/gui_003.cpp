void gui_003::onHighResolutionRegion( QRect SelectionRect)
{
	remove( "temp_highresolution.jpg");
	Player->Stop = true;
	getCapture( 0, "temp_highresolution.jpg");

	HighResInspectionWindow = new InspectionWindow();
	HighResInspectionWindow->HighResInspectionView->centerOn( 2464 * (double)SelectionRect.center().x() / GraphicsView->rect().width(),
															  1632 * (double)SelectionRect.center().y() / GraphicsView->rect().height());
	HighResInspectionWindow->HighResInspectionView->setMinimumSize( (int)( SelectionRect.width() * 2464 / (double) 640),
																	(int)( SelectionRect.height()* 1632 / (double) 426));
	HighResInspectionWindow->HighResInspectionView->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum);	
	HighResInspectionWindow->setCentralWidget( HighResInspectionWindow->HighResInspectionView);
	HighResInspectionWindow->show();

	finalizeCamera();
	Player->Stop = false;
	Player->start();
}