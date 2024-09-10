// --------------------------------------------------------------------------
void voDelimitedTextPreviewModel::updatePreview()
{
  Q_D(voDelimitedTextPreviewModel);

  if (d->SampleCacheFile.fileName().isEmpty())
    {
    //qWarning() << QObject::tr("ERROR: updatePreview: SampleCacheFile filename not set");
    return;
    }

  // Setup vtkDelimitedTextReader
  vtkNew<vtkDelimitedTextReader> previewReader;
  d->configureReader(previewReader.GetPointer());

  // Read in file to table
  previewReader->Update();
  vtkSmartPointer<vtkTable> table = previewReader->GetOutput();

  if (d->Transpose)
    {
    // Assumes there is a header column ... which we have no setting to specify for anyway
    voUtils::transposeTable(table);
    }

  // Build model (self)
  this->clear();

  // Clear original data table
  while (d->OriginalDataTable->GetNumberOfColumns() > 0)
    {
    d->OriginalDataTable->RemoveColumn(d->OriginalDataTable->GetNumberOfColumns() - 1); // columns should be named
    }

  // Update metadata preview and set DataTable
  QColor headerBackgroundColor = QPalette().color(QPalette::Window);
  QColor ofInterestBackgroundColor = QPalette().color(QPalette::Mid);

  for (vtkIdType cid = 0; cid < table->GetNumberOfColumns(); ++cid)
    {
    vtkStringArray * column = vtkStringArray::SafeDownCast(table->GetColumn(cid));
    Q_ASSERT(column);
    vtkSmartPointer<vtkStringArray> dataColumn;
    if (cid >= d->NumberOfRowMetaDataTypes)
      {
      dataColumn = vtkSmartPointer<vtkStringArray>::New();
      dataColumn->SetName(QString::number(cid - d->NumberOfRowMetaDataTypes + 1).toLatin1());
      dataColumn->SetNumberOfValues(column->GetNumberOfValues() - d->NumberOfColumnMetaDataTypes);
      }
    for (int rid = 0; rid < column->GetNumberOfValues(); ++rid)
      {
      QString value = QString(column->GetValue(rid));
      QStandardItem* currentItem = 0;
      if (rid == d->ColumnMetaDataTypeOfInterest || cid == d->RowMetaDataTypeOfInterest)
        {
        this->setItem(rid, cid, (currentItem = new QStandardItem(value)));
        currentItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        currentItem->setData(ofInterestBackgroundColor, Qt::BackgroundRole);
        }
      else if (rid < d->NumberOfColumnMetaDataTypes || cid < d->NumberOfRowMetaDataTypes)
        {
        this->setItem(rid, cid, (currentItem = new QStandardItem(value)));
        currentItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        currentItem->setData(headerBackgroundColor, Qt::BackgroundRole);
        }
      else
        {
        dataColumn->SetValue(rid - d->NumberOfColumnMetaDataTypes, value.toLatin1());
        }
      }
    if (cid >= d->NumberOfRowMetaDataTypes)
      {
      d->OriginalDataTable->AddColumn(dataColumn.GetPointer());
      }
    }

  // TODO: Add missing value identification/rectification step
  vtkNew<vtkStringToNumeric> numericToStringFilter;
  numericToStringFilter->SetInputData(d->OriginalDataTable.GetPointer());
  numericToStringFilter->Update();
  vtkTable * numericDataTable = vtkTable::SafeDownCast(numericToStringFilter->GetOutput());
  Q_ASSERT(numericDataTable);
  d->OriginalDataTable = numericDataTable;

  // Remove data table observer, copy data, and re-add observer
  d->DataTable->RemoveObserver(d->UpdateDataPreviewCallbackCommand);
  this->resetDataTable();
  d->DataTable->AddObserver(vtkCommand::ModifiedEvent, d->UpdateDataPreviewCallbackCommand);

  d->updateDataPreview();
}