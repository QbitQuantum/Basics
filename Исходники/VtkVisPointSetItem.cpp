void VtkVisPointSetItem::Initialize(vtkRenderer* renderer)
{
    // TODO vtkTransformFilter creates a new copy of the point coordinates which
    // conflicts with VtkMappedMeshSource. Find a workaround!
    _transformFilter = vtkTransformFilter::New();
    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    transform->Identity();
    _transformFilter->SetTransform(transform);

    _transformFilter->SetInputConnection(_algorithm->GetOutputPort());
    _transformFilter->Update();

    _renderer = renderer;
    _mapper = QVtkDataSetMapper::New();
    _mapper->InterpolateScalarsBeforeMappingOff();
    _mapper->SetColorModeToMapScalars();

    _mapper->SetInputConnection(_transformFilter->GetOutputPort());
    _actor = vtkActor::New();
    static_cast<vtkActor*>(_actor)->SetMapper(_mapper);
    _renderer->AddActor(_actor);

    // Determine the right pre-set properties
    // Order is: _algorithm, _compositeFilter, create a new one with props copied from parent
    VtkAlgorithmProperties* vtkProps = dynamic_cast<VtkAlgorithmProperties*>(_algorithm);
    if (!vtkProps)
    {
        vtkProps = dynamic_cast<VtkAlgorithmProperties*>(_compositeFilter);

        // Copy properties from parent or create a new VtkAlgorithmProperties
        if (!vtkProps)
        {
            VtkVisPipelineItem* parentItem = dynamic_cast<VtkVisPipelineItem*>(this->parentItem());
            while (parentItem)
            {
                VtkAlgorithmProperties* parentProps = nullptr;
                if(dynamic_cast<VtkVisPointSetItem*>(parentItem))
                    parentProps = dynamic_cast<VtkVisPointSetItem*>(parentItem)->getVtkProperties();
                if (parentProps)
                {
                    vtkProps = new VtkAlgorithmProperties(); // TODO memory leak?
                    vtkProps->SetScalarVisibility(parentProps->GetScalarVisibility());
                    vtkProps->SetTexture(parentProps->GetTexture());
                    vtkProps->SetActiveAttribute(parentProps->GetActiveAttribute());
                    parentItem = nullptr;
                }
                else
                    parentItem = dynamic_cast<VtkVisPipelineItem*>(parentItem->parentItem());
            }

            // Has no parents
            if (!vtkProps)
                vtkProps = new VtkAlgorithmProperties(); // TODO memory leak?
        }
    }
    _vtkProps = vtkProps;

    if (vtkProps->GetActiveAttribute().length() == 0)
    {
        // Get first scalar and set it to active
        QStringList arrayNames = this->getScalarArrayNames();
        if (arrayNames.length() > 0)
            vtkProps->SetActiveAttribute(arrayNames[0]);
        else
            vtkProps->SetActiveAttribute("Solid Color");
    }
    this->setVtkProperties(vtkProps);
    this->SetActiveAttribute(vtkProps->GetActiveAttribute());


    // Set global backface culling
    QSettings settings;
    bool backfaceCulling = settings.value("globalCullBackfaces", 0).toBool();
    this->setBackfaceCulling(backfaceCulling);

    // Set the correct threshold range
    if (dynamic_cast<VtkCompositeThresholdFilter*>(this->_compositeFilter) )
    {
        double range[2];
        this->GetRangeForActiveAttribute(range);
        QList<QVariant> thresholdRangeList;
        thresholdRangeList.push_back(range[0]);
        thresholdRangeList.push_back(range[1]);
        dynamic_cast<VtkCompositeFilter*>(this->_compositeFilter)
            ->SetUserVectorProperty("Range", thresholdRangeList);
    }

    // Show edges on meshes
    if (dynamic_cast<MeshLib::VtkMappedMeshSource*>(this->_algorithm))
        _vtkProps->GetProperties()->SetEdgeVisibility(1);
}