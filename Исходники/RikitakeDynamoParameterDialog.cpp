GLMotif::PopupWindow* RikitakeDynamoParameterDialog::createDialog()
{
  WidgetFactory factory;
  GLMotif::PopupWindow* parameterDialogPopup=factory.createPopupWindow("ParameterDialogPopup", "RikitakeDynamo Parameters");

  GLMotif::RowColumn* parameterDialog=factory.createRowColumn("ParameterDialog", 3);
  factory.setLayout(parameterDialog);

  factory.createLabel("NuParameterLabel", "nu");

  currentNuValue=factory.createTextField("CurrentNuValue", 10);
  currentNuValue->setString("0.2");

  nuParameterSlider=factory.createSlider("NuParameterSlider", 15.0);
  nuParameterSlider->setValueRange(0.0, 10.0, 0.01);
  nuParameterSlider->setValue(0.2);
  nuParameterSlider->getValueChangedCallbacks().add(this, &RikitakeDynamoParameterDialog::sliderCallback);

  factory.createLabel("AParameterLabel", "a");

  currentAValue=factory.createTextField("CurrentAValue", 10);
  currentAValue->setString("5.0");

  aParameterSlider=factory.createSlider("AParameterSlider", 15.0);
  aParameterSlider->setValueRange(0.0, 10.0, 0.01);
  aParameterSlider->setValue(5.0);
  aParameterSlider->getValueChangedCallbacks().add(this, &RikitakeDynamoParameterDialog::sliderCallback);


  factory.createLabel("StepSizeLabel", "step size");
  stepSizeValue=factory.createTextField("StepSizeValue", 10);
  double step_size = IntegrationStepSize::instance()->getSavedValue("Rikitake Dynamo");
  if (step_size > 0.0) stepSizeValue->setString(toString(step_size).c_str());
  else stepSizeValue->setString("0.01");
  stepSizeSlider=factory.createSlider("StepSizeSlider", 15.0);
  stepSizeSlider->setValueRange(0.0001, 0.05, 0.0001);
  if (step_size > 0.0) stepSizeSlider->setValue(step_size);
  else stepSizeSlider->setValue(0.01);
  stepSizeSlider->getValueChangedCallbacks().add(this, &RikitakeDynamoParameterDialog::sliderCallback);


  factory.createLabel("EvaluationLabel", "Evaluation Method");
  GLMotif::ToggleButton* exactEvalToggle=factory.createCheckBox("ExactEvalToggle", "Exact", true);
  GLMotif::ToggleButton* gridEvalToggle=factory.createCheckBox("GridEvalToggle", "Interpolated Grid");
  // assign line style toggle callbacks
  exactEvalToggle->getValueChangedCallbacks().add(this, &RikitakeDynamoParameterDialog::evalTogglesCallback);
  gridEvalToggle->getValueChangedCallbacks().add(this, &RikitakeDynamoParameterDialog::evalTogglesCallback);

  factory.createLabel("xSpacingLabel", "x-Grid Spacing");
  currentXValue=factory.createTextField("xTextField", 12);
  currentXValue->setString("1.0");
  currentXValue->setCharWidth(5);
  currentXValue->setPrecision(5);
  xSpacingSlider=factory.createSlider("XSpacingSlider", 15.0);
  xSpacingSlider->setValueRange(.001, 2.0, 0.001);
  xSpacingSlider->setValue(1.0);
  xSpacingSlider->getValueChangedCallbacks().add(this, &RikitakeDynamoParameterDialog::sliderCallback);

  factory.createLabel("ySpacingLabel", "y-Grid Spacing");
  currentYValue=factory.createTextField("yTextField", 12);
  currentYValue->setString("1.0");
  currentYValue->setCharWidth(5);
  currentYValue->setPrecision(5);  ySpacingSlider=factory.createSlider("YSpacingSlider", 15.0);
  ySpacingSlider->setValueRange(.001, 2.0, 0.001);
  ySpacingSlider->setValue(1.0);
  ySpacingSlider->getValueChangedCallbacks().add(this, &RikitakeDynamoParameterDialog::sliderCallback);

  factory.createLabel("zSpacingLabel", "z-Grid Spacing");
  currentZValue=factory.createTextField("zTextField", 12);
  currentZValue->setString("1.0");
  currentZValue->setCharWidth(5);
  currentZValue->setPrecision(5);
  zSpacingSlider=factory.createSlider("ZSpacingSlider", 15.0);
  zSpacingSlider->setValueRange(.001, 2.0, 0.001);
  zSpacingSlider->setValue(1.0);
  zSpacingSlider->getValueChangedCallbacks().add(this, &RikitakeDynamoParameterDialog::sliderCallback);

  // add toggles to array for radio-button behavior
  evalToggles.push_back(exactEvalToggle);
  evalToggles.push_back(gridEvalToggle);

  parameterDialog->manageChild();
  return parameterDialogPopup;
}