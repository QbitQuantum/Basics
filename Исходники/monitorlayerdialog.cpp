void MonitorLayerDialog::loadSettings()
{
	MonitorLayer *layer = static_cast<MonitorLayer *>(m_layer);

	// As we assume the monitor list hasn't changed since it was populated just
	// refresh it again to be safe
	refreshMonitorList();

	// Monitor combo
	int monitor = layer->getMonitor();
	for(int i = 0; i < m_ui.monitorCombo->count(); i++) {
		int friendlyId = m_ui.monitorCombo->itemData(i, Qt::UserRole).toInt();
		if(monitor == friendlyId) {
			m_ui.monitorCombo->setCurrentIndex(i);
			break;
		}
	}

	// Mouse cursor
	m_ui.showCursorBtn->setChecked(layer->getCaptureMouse());
	m_ui.hideCursorBtn->setChecked(!layer->getCaptureMouse());

	// Disable Windows Aero
	if(!IsWindows8OrGreater()) {
		m_ui.ignoreAeroBtn->setChecked(!layer->getDisableAero());
		m_ui.disableAeroBtn->setChecked(layer->getDisableAero());
	}

	// Cropping information
	const CropInfo &cropInfo = layer->getCropInfo();
	m_ui.leftCropEdit->setText(QString::number(cropInfo.getLeftMargin()));
	m_ui.rightCropEdit->setText(QString::number(cropInfo.getRightMargin()));
	m_ui.topCropEdit->setText(QString::number(cropInfo.getTopMargin()));
	m_ui.botCropEdit->setText(QString::number(cropInfo.getBottomMargin()));
	m_ui.leftCropAnchorBox->setCurrentIndex((int)cropInfo.getLeftAnchor());
	m_ui.rightCropAnchorBox->setCurrentIndex((int)cropInfo.getRightAnchor());
	m_ui.topCropAnchorBox->setCurrentIndex((int)cropInfo.getTopAnchor());
	m_ui.botCropAnchorBox->setCurrentIndex((int)cropInfo.getBottomAnchor());

	// Colour adjustment
	m_ignoreSignals = true;
	m_ui.gammaSlider->setValue(qRound(log10(layer->getGamma()) * 500.0f));
	m_ui.gammaBox->setValue(layer->getGamma());
	m_ui.brightnessSlider->setValue(layer->getBrightness());
	m_ui.brightnessBox->setValue(layer->getBrightness());
	m_ui.contrastSlider->setValue(layer->getContrast());
	m_ui.contrastBox->setValue(layer->getContrast());
	m_ui.saturationSlider->setValue(layer->getSaturation());
	m_ui.saturationBox->setValue(layer->getSaturation());
	m_ignoreSignals = false;
}