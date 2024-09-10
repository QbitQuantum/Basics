GLMotif::PopupWindow* DotSpreaderOptionsDialog::createDialog()
{
   WidgetFactory factory;

   // create popup-shell
   GLMotif::PopupWindow* parameterDialogPopup=factory.createPopupWindow("ParameterDialogPopup", "Dot Spreader Options");

   // create the main layout
   GLMotif::RowColumn* parameterDialog=factory.createRowColumn("ParameterDialog", 3);
   factory.setLayout(parameterDialog);

   factory.createLabel("", "NumberOfParticles");

   // create text field
   numberOfParticlesValue=factory.createTextField("NumberOfParticlesTextField", 10);
   numberOfParticlesValue->setString("10000");

   // create and initialize slider object
   numberOfParticlesSlider=factory.createSlider("NumberOfParticlesSlider", 15.0);
   numberOfParticlesSlider->setValueRange(1000.0, 250000.0, 1000.0);
   numberOfParticlesSlider->setValue(10000.0);

   // set the slider callback
   numberOfParticlesSlider->getValueChangedCallbacks().add(this, &DotSpreaderOptionsDialog::sliderCallback);

   factory.createLabel("ParticleSizeLabel", "Particle Size");

   pointSizeValue=factory.createTextField("PointSizeTextField", 10);
   pointSizeValue->setString("0.05");

   pointSizeSlider=factory.createSlider("PointSizeSlider", 15.0);
   pointSizeSlider->setValueRange(0.01, 1.0, 0.05);
   pointSizeSlider->setValue(0.05);

   pointSizeSlider->getValueChangedCallbacks().add(this, &DotSpreaderOptionsDialog::sliderCallback);

   // create distribution check boxes
   GLMotif::ToggleButton* surfaceDistributionToggle=factory.createCheckBox("SurfaceDistributionToggle", "Surface", true);
   GLMotif::ToggleButton* volumeDistributionToggle=factory.createCheckBox("VolumeDistributionToggle", "Volume");

   // set callbacks for toggle buttons (check boxes)
   surfaceDistributionToggle->getValueChangedCallbacks().add(this, &DotSpreaderOptionsDialog::distributionTogglesCallback);
   volumeDistributionToggle->getValueChangedCallbacks().add(this, &DotSpreaderOptionsDialog::distributionTogglesCallback);

   // add toggle buttons to array for radio-button behavior
   distributionToggles.push_back(surfaceDistributionToggle);
   distributionToggles.push_back(volumeDistributionToggle);

   // create push buttons
   clearParticles = factory.createButton("ClearParticles", "Clear Particles");

   // assign callbacks for buttons
   clearParticles->getSelectCallbacks().add(this, &DotSpreaderOptionsDialog::buttonCallback);

   parameterDialog->manageChild();

   return parameterDialogPopup;
}