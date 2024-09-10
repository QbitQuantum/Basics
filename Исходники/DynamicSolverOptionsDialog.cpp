GLMotif::PopupWindow* DynamicSolverOptionsDialog::createDialog()
{
   WidgetFactory factory;

   // create the popup-shell
   GLMotif::PopupWindow* parameterDialogPopup=factory.createPopupWindow("ParameterDialogPopup", " Dynamic Solver Options");

   // create the main layout
   GLMotif::RowColumn* parameterDialog=factory.createRowColumn("ParameterDialog", 1);
   factory.setLayout(parameterDialog);

   // create a layout for check boxes (toggle buttons)
   GLMotif::RowColumn* checkBoxLayout=factory.createRowColumn("CheckBoxLayout", 4);
   factory.setLayout(checkBoxLayout);

   // create line style toggle buttons (check boxes)
   factory.createLabel("", "Line Style");
   GLMotif::ToggleButton* noneLineToggle=
         factory.createCheckBox("NoneLineToggle", "None");
   GLMotif::ToggleButton* basicLineToggle=
         factory.createCheckBox("BasicLineToggle", "2D");
   GLMotif::ToggleButton* polyLineToggle=
         factory.createCheckBox("PolyLineToggle", "3D", true);

   // assign callbacks for line style toggle buttons
   noneLineToggle->getValueChangedCallbacks().add(this, &DynamicSolverOptionsDialog::lineStyleTogglesCallback);
   basicLineToggle->getValueChangedCallbacks().add(this, &DynamicSolverOptionsDialog::lineStyleTogglesCallback);
   polyLineToggle->getValueChangedCallbacks().add(this, &DynamicSolverOptionsDialog::lineStyleTogglesCallback);

   // add line style toggles to array for radio-button behavior
   lineStyleToggles.push_back(noneLineToggle);
   lineStyleToggles.push_back(basicLineToggle);
   lineStyleToggles.push_back(polyLineToggle);

   // create head style toggle buttons (check boxes)
   factory.createLabel("", "Head Style");
   GLMotif::ToggleButton* noneHeadToggle=factory.createCheckBox("NoneHeadToggle", "None");
   GLMotif::ToggleButton* pointHeadToggle=factory.createCheckBox("PointHeadToggle", "Point", true);
   GLMotif::ToggleButton* sphereHeadToggle=factory.createCheckBox("SphereHeadToggle", "Sphere");

   // assign callbacks for head style toggle buttons
   noneHeadToggle->getValueChangedCallbacks().add(this, &DynamicSolverOptionsDialog::headStyleTogglesCallback);
   pointHeadToggle->getValueChangedCallbacks().add(this, &DynamicSolverOptionsDialog::headStyleTogglesCallback);
   sphereHeadToggle->getValueChangedCallbacks().add(this, &DynamicSolverOptionsDialog::headStyleTogglesCallback);

   // add head style toggles to array for radio-button behavior
   headStyleToggles.push_back(noneHeadToggle);
   headStyleToggles.push_back(pointHeadToggle);
   headStyleToggles.push_back(sphereHeadToggle);

   // create color style toggle buttons (check boxes)
   factory.createLabel("", "Color Map");
   GLMotif::ToggleButton* solidColorToggle=factory.createCheckBox("SolidColorToggle", "Solid", true);
   GLMotif::ToggleButton* gradientColorToggle=factory.createCheckBox("GradientColorToggle", "Gradient");

   // assign callbacks for color style toggle buttons
   solidColorToggle->getValueChangedCallbacks().add(this, &DynamicSolverOptionsDialog::colorStyleTogglesCallback);
   gradientColorToggle->getValueChangedCallbacks().add(this, &DynamicSolverOptionsDialog::colorStyleTogglesCallback);

   // add color style toggles to array for radio-button behavior
   colorMapToggles.push_back(solidColorToggle);
   colorMapToggles.push_back(gradientColorToggle);

   // create spacer (newline)
   factory.createLabel("Spacer", "");

   checkBoxLayout->manageChild();

   factory.setLayout(parameterDialog);

   // create layout for sliders
   GLMotif::RowColumn* sliderLayout=factory.createRowColumn("SliderLayout", 3);
   factory.setLayout(sliderLayout);

   factory.createLabel("ReleaseSizeLabel", "Number of Particles");

   releaseSizeValue=factory.createTextField("ReleaseSizeTextField", 10);
   releaseSizeValue->setString("1");

   releaseSizeSlider=factory.createSlider("ReleaseSizeSlider", 15.0);
   releaseSizeSlider->setValueRange(1, 250, 1);
   releaseSizeSlider->setValue(1);

   releaseSizeSlider->getValueChangedCallbacks().add(this, &DynamicSolverOptionsDialog::sliderCallback);

   factory.createLabel("ParticleSizeLabel", "Particle Size");

   pointSizeValue=factory.createTextField("PointSizeTextField", 10);
   pointSizeValue->setString("0.25");

   pointSizeSlider=factory.createSlider("PointSizeSlider", 15.0);
   pointSizeSlider->setValueRange(0.01, 0.25, 0.01);
   pointSizeSlider->setValue(0.25);

   pointSizeSlider->getValueChangedCallbacks().add(this, &DynamicSolverOptionsDialog::sliderCallback);

   // create a push button for clearing particles and assign callback
   GLMotif::Button* clearButton=factory.createButton("ClearButton", "Clear");
   clearButton->getSelectCallbacks().add(this, &DynamicSolverOptionsDialog::clearPointsCallback);

   sliderLayout->manageChild();

   parameterDialog->manageChild();

   return parameterDialogPopup;
}