/**
* Set the offset in u-coordinate of a 2d (unwrapped) surface
*/
void InstrumentWidgetRenderTab::setUCorrection() {
  auto surface = getSurface();
  auto rotSurface = boost::dynamic_pointer_cast<RotationSurface>(surface);
  if (rotSurface) {
    QPointF oldUCorr = rotSurface->getUCorrection();
    // ask the user to enter a number for the u-correction
    UCorrectionDialog dlg(this, oldUCorr, rotSurface->isManualUCorrection());
    if (dlg.exec() != QDialog::Accepted)
      return;

    QSettings settings;
    settings.beginGroup(m_instrWidget->getInstrumentSettingsGroupName());

    if (dlg.applyCorrection()) {
      QPointF ucorr = dlg.getValue();
      // update the surface only if the correction changes
      if (ucorr != oldUCorr) {
        rotSurface->setUCorrection(ucorr.x(),
                                   ucorr.y()); // manually set the correction
        rotSurface->requestRedraw();           // redraw the view
        settings.setValue(EntryManualUCorrection, true);
        settings.setValue(EntryUCorrectionMin, ucorr.x());
        settings.setValue(EntryUCorrectionMax, ucorr.y());
      }
    } else {
      rotSurface->setAutomaticUCorrection(); // switch to automatic correction
      rotSurface->requestRedraw();           // redraw the view
      settings.remove(EntryManualUCorrection);
      settings.remove(EntryUCorrectionMin);
      settings.remove(EntryUCorrectionMax);
    }
  }
}