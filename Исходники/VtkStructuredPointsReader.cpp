// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void VtkStructuredPointsReader::dataCheck()
{
  initialize();
  setErrorCondition(0);

  QFileInfo fi(getInputFile());
  if (getInputFile().isEmpty() == true)
  {
    QString ss = QObject::tr("The input file must be set");
    setErrorCondition(-61000);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  else if (fi.exists() == false)
  {
    QString ss = QObject::tr("The input file does not exist");
    setErrorCondition(-61001);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }

  // First shot Sanity Checks.
  if(!getReadCellData() && !getReadPointData())
  {
    QString ss = QObject::tr("At least one of Read Point Data or Read Cell Data must be checked");
    setErrorCondition(-61002);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }

  // Last chance sanity check
  if(getErrorCondition() < 0) { return; }

  // Create a Vertex Data Container even though we may remove it later. We need it later
  // on in order to set the proper AttributeMatrix
  DataContainer::Pointer pointData_DataContainer = getDataContainerArray()->createNonPrereqDataContainer<AbstractFilter>(this, getVertexDataContainerName());
  if(getErrorCondition() < 0 && NULL == pointData_DataContainer) { return; }

  ImageGeom::Pointer pointDataGeom = ImageGeom::CreateGeometry(getVertexDataContainerName());
  pointData_DataContainer->setGeometry(pointDataGeom);

  QVector<size_t> tDims(1, 0);
  AttributeMatrix::Pointer pointAttrMat = pointData_DataContainer->createNonPrereqAttributeMatrix<AbstractFilter>(this, getVertexAttributeMatrixName(), tDims, SIMPL::AttributeMatrixType::Cell);
  if(getErrorCondition() < 0) { return; }

  // Create a Volume Data Container even though we may remove it later. We need it later
  // on in order to set the proper AttributeMatrix
  DataContainer::Pointer cellData_DataContainer = getDataContainerArray()->createNonPrereqDataContainer<AbstractFilter>(this, getVolumeDataContainerName());
  if(getErrorCondition() < 0 && NULL == cellData_DataContainer) { return; }

  ImageGeom::Pointer cellDataGeom = ImageGeom::CreateGeometry(getVolumeDataContainerName());
  cellData_DataContainer->setGeometry(cellDataGeom);

  tDims.resize(3);
  tDims[0] = 0;
  tDims[1] = 0;
  tDims[2] = 0;
  AttributeMatrix::Pointer cellAttrMat = cellData_DataContainer->createNonPrereqAttributeMatrix<AbstractFilter>(this, getCellAttributeMatrixName(), tDims, SIMPL::AttributeMatrixType::Cell);
  if(getErrorCondition() < 0) { return; }

  // Scan through the file
  readFile();

  // now check to see what the user wanted
  if (!getReadPointData())
  {
    getDataContainerArray()->removeDataContainer(getVertexDataContainerName());
  }
  if (!getReadCellData())
  {
    getDataContainerArray()->removeDataContainer(getVolumeDataContainerName());
  }

  // If there was no Cell Data, remove that dataContainer
  if (cellAttrMat->getNumAttributeArrays() == 0)
  {
    getDataContainerArray()->removeDataContainer(getVolumeDataContainerName());
  }

  // If there were no Point Arrays then remove that dataContainer
  if (pointAttrMat->getNumAttributeArrays() == 0)
  {
    getDataContainerArray()->removeDataContainer(getVertexDataContainerName());
  }
}