GLMotif::PopupWindow* CartesianGrid3DParameterDialog::createDialog()
{
  WidgetFactory factory;
  GLMotif::PopupWindow* parameterDialogPopup=factory.createPopupWindow("ParameterDialogPopup", "CartesianGrid3D Parameters");

  GLMotif::RowColumn* parameterDialog=factory.createRowColumn("ParameterDialog", 3);
  factory.setLayout(parameterDialog);
   
  openFileButton = factory.createButton("OpenFileButton", "Load Data");
  openFileStatusA = factory.createLabel("OpenFileStatusA", "");
  openFileStatusB = factory.createLabel("OpenFileStatusB", "");
  openFileButton->getSelectCallbacks().add(this, &CartesianGrid3DParameterDialog::openFileCallback);

  char cwd[512];
  getcwd(cwd, 512);
  std::string dataDirectory(cwd);
  IO::DirectoryPtr dirptr = IO::openDirectory(dataDirectory.c_str());

  fileDialog = new GLMotif::FileSelectionDialog(Vrui::getWidgetManager(), "Open file...", dirptr, ".grid");
  // Need to modify FileSelectionDialog to accept filterDescriptions. For ex: "Simple Grid (.grid)"
  //  fileDialog->addFileNameFilters("Numpy Array (.npy)");
  fileDialog->getOKCallbacks().add(this, &CartesianGrid3DParameterDialog::fileOpenAction);
  fileDialog->getCancelCallbacks().add(this, &CartesianGrid3DParameterDialog::fileCancelAction);

/*  factory.createLabel("Dummy3", "");
  openFileStatusC = factory.createLabel("OpenFileStatusC", "");
  factory.createLabel("Dummy4", "");
*/

  factory.createLabel("Dummy3b", "");
  shapeLabel = factory.createLabel("ShapeLabel", "");
  shapeValue = factory.createLabel("ShapeValue", "");

  factory.createLabel("Dummy5", "");
  factory.createLabel("Dummy6", "");
  factory.createLabel("Dummy7", "");

  factory.createLabel("StepSizeLabel", "step size");
  stepSizeValue=factory.createTextField("StepSizeValue", 10);
  double step_size = IntegrationStepSize::instance()->getSavedValue("CartesianGrid3D");
  if (step_size > 0.0) stepSizeValue->setString(toString(step_size).c_str());
  else stepSizeValue->setString("0.01");
  stepSizeSlider=factory.createSlider("StepSizeSlider", 15.0);
  stepSizeSlider->setValueRange(0.0001, 0.05, 0.0001);
  if (step_size > 0.0) stepSizeSlider->setValue(step_size);
  else stepSizeSlider->setValue(0.01);
  stepSizeSlider->getValueChangedCallbacks().add(this, &CartesianGrid3DParameterDialog::sliderCallback);

  parameterDialog->manageChild();
  return parameterDialogPopup;
}