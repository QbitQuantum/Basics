void dialogAnalog::updatecapture(int state)
{
    mainwindow->analogMutex.lock();

	if (state == Qt::Checked )
	{
		setCapture(true);
		dataplot.Clear();
		pbZoomIn->setEnabled(false);
		pbZoomOut->setEnabled(false);
		pbFit->setEnabled(false);
		pbSave->setEnabled(false);
		pbLoad->setEnabled(false);
		groupBox->setEnabled(false);
		chkBShowMarker->setEnabled(false);
		
	}
	else
	{
		setCapture(false);
		// Store timeref
        dataplot.timeUnit = ( pPC->pTIMER->CPUSpeed * pPC->getfrequency() );
		ComputeScrollBar();
		
		pbZoomIn->setEnabled(true);
		pbZoomOut->setEnabled(true);
		pbFit->setEnabled(true);
		pbSave->setEnabled(true);
		pbLoad->setEnabled(true);
		groupBox->setEnabled(true);
		chkBShowMarker->setEnabled(true);

		this->update();
	}
    mainwindow->analogMutex.unlock();
}