void TractsToVectorImageFilter< PixelType >::GenerateData()
{
    mitk::BaseGeometry::Pointer geometry = m_FiberBundle->GetGeometry();

    // calculate new image parameters
    itk::Vector<double> spacing;
    itk::Point<double> origin;
    itk::Matrix<double, 3, 3> direction;
    ImageRegion<3> imageRegion;
    if (!m_MaskImage.IsNull())
    {
        spacing = m_MaskImage->GetSpacing();
        imageRegion = m_MaskImage->GetLargestPossibleRegion();
        origin = m_MaskImage->GetOrigin();
        direction = m_MaskImage->GetDirection();
    }
    else
    {
        spacing = geometry->GetSpacing();
        origin = geometry->GetOrigin();
        mitk::BaseGeometry::BoundsArrayType bounds = geometry->GetBounds();
        origin[0] += bounds.GetElement(0);
        origin[1] += bounds.GetElement(2);
        origin[2] += bounds.GetElement(4);

        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                direction[j][i] = geometry->GetMatrixColumn(i)[j];
        imageRegion.SetSize(0, geometry->GetExtent(0));
        imageRegion.SetSize(1, geometry->GetExtent(1));
        imageRegion.SetSize(2, geometry->GetExtent(2));


        m_MaskImage = ItkUcharImgType::New();
        m_MaskImage->SetSpacing( spacing );
        m_MaskImage->SetOrigin( origin );
        m_MaskImage->SetDirection( direction );
        m_MaskImage->SetRegions( imageRegion );
        m_MaskImage->Allocate();
        m_MaskImage->FillBuffer(1);
    }
    OutputImageType::RegionType::SizeType outImageSize = imageRegion.GetSize();
    m_OutImageSpacing = m_MaskImage->GetSpacing();
    m_ClusteredDirectionsContainer = ContainerType::New();

    // initialize num directions image
    m_NumDirectionsImage = ItkUcharImgType::New();
    m_NumDirectionsImage->SetSpacing( spacing );
    m_NumDirectionsImage->SetOrigin( origin );
    m_NumDirectionsImage->SetDirection( direction );
    m_NumDirectionsImage->SetRegions( imageRegion );
    m_NumDirectionsImage->Allocate();
    m_NumDirectionsImage->FillBuffer(0);

    // initialize direction images
    m_DirectionImageContainer = DirectionImageContainerType::New();

    // resample fiber bundle
    double minSpacing = 1;
    if(m_OutImageSpacing[0]<m_OutImageSpacing[1] && m_OutImageSpacing[0]<m_OutImageSpacing[2])
        minSpacing = m_OutImageSpacing[0];
    else if (m_OutImageSpacing[1] < m_OutImageSpacing[2])
        minSpacing = m_OutImageSpacing[1];
    else
        minSpacing = m_OutImageSpacing[2];

    if (m_UseWorkingCopy)
        m_FiberBundle = m_FiberBundle->GetDeepCopy();

    // resample fiber bundle for sufficient voxel coverage
    m_FiberBundle->ResampleSpline(minSpacing/10);

    // iterate over all fibers
    vtkSmartPointer<vtkPolyData> fiberPolyData = m_FiberBundle->GetFiberPolyData();
    int numFibers = m_FiberBundle->GetNumFibers();
    m_DirectionsContainer = ContainerType::New();

    VectorContainer< unsigned int, std::vector< double > >::Pointer peakLengths = VectorContainer< unsigned int, std::vector< double > >::New();

    MITK_INFO << "Generating directions from tractogram";
    boost::progress_display disp(numFibers);
    for( int i=0; i<numFibers; i++ )
    {
        ++disp;
        vtkCell* cell = fiberPolyData->GetCell(i);
        int numPoints = cell->GetNumberOfPoints();
        vtkPoints* points = cell->GetPoints();
        if (numPoints<2)
            continue;

        vnl_vector_fixed<double, 3> dir;
        itk::Point<double, 3> worldPos;
        vnl_vector<double> v;


        float fiberWeight = m_FiberBundle->GetFiberWeight(i);

        for( int j=0; j<numPoints-1; j++)
        {
            // get current position along fiber in world coordinates
            double* temp = points->GetPoint(j);
            worldPos = GetItkPoint(temp);
            itk::Index<3> index;
            m_MaskImage->TransformPhysicalPointToIndex(worldPos, index);
            if (!m_MaskImage->GetLargestPossibleRegion().IsInside(index) || m_MaskImage->GetPixel(index)==0)
                continue;

            // get fiber tangent direction at this position
            v = GetVnlVector(temp);
            dir = GetVnlVector(points->GetPoint(j+1))-v;
            if (dir.is_zero())
                continue;
            dir.normalize();

            // add direction to container
            unsigned int idx = index[0] + outImageSize[0]*(index[1] + outImageSize[1]*index[2]);
            DirectionContainerType::Pointer dirCont;
            if (m_DirectionsContainer->IndexExists(idx))
            {
                peakLengths->ElementAt(idx).push_back(fiberWeight);

                dirCont = m_DirectionsContainer->GetElement(idx);
                if (dirCont.IsNull())
                {
                    dirCont = DirectionContainerType::New();
                    dirCont->push_back(dir);
                    m_DirectionsContainer->InsertElement(idx, dirCont);
                }
                else
                    dirCont->push_back(dir);
            }
            else
            {
                dirCont = DirectionContainerType::New();
                dirCont->push_back(dir);
                m_DirectionsContainer->InsertElement(idx, dirCont);

                std::vector< double > lengths; lengths.push_back(fiberWeight);
                peakLengths->InsertElement(idx, lengths);
            }
        }
    }

    vtkSmartPointer<vtkCellArray> m_VtkCellArray = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkPoints>    m_VtkPoints = vtkSmartPointer<vtkPoints>::New();

    itk::ImageRegionIterator<ItkUcharImgType> dirIt(m_NumDirectionsImage, m_NumDirectionsImage->GetLargestPossibleRegion());

    MITK_INFO << "Clustering directions";
    boost::progress_display disp2(outImageSize[0]*outImageSize[1]*outImageSize[2]);
    while(!dirIt.IsAtEnd())
    {
        ++disp2;
        OutputImageType::IndexType index = dirIt.GetIndex();
        int idx = index[0]+(index[1]+index[2]*outImageSize[1])*outImageSize[0];

        if (!m_DirectionsContainer->IndexExists(idx))
        {
            ++dirIt;
            continue;
        }
        DirectionContainerType::Pointer dirCont = m_DirectionsContainer->GetElement(idx);
        if (dirCont.IsNull() || dirCont->empty())
        {
            ++dirIt;
            continue;
        }

//        std::vector< double > lengths; lengths.resize(dirCont->size(), 1);  // all peaks have size 1
        DirectionContainerType::Pointer directions;
        if (m_MaxNumDirections>0)
        {
            directions = FastClustering(dirCont, peakLengths->GetElement(idx));
            std::sort( directions->begin(), directions->end(), CompareVectorLengths );
        }
        else
            directions = dirCont;

        unsigned int numDir = directions->size();
        if (m_MaxNumDirections>0 && numDir>m_MaxNumDirections)
            numDir = m_MaxNumDirections;

        int count = 0;
        for (unsigned int i=0; i<numDir; i++)
        {
            vtkSmartPointer<vtkPolyLine> container = vtkSmartPointer<vtkPolyLine>::New();
            itk::ContinuousIndex<double, 3> center;
            center[0] = index[0];
            center[1] = index[1];
            center[2] = index[2];
            itk::Point<double> worldCenter;
            m_MaskImage->TransformContinuousIndexToPhysicalPoint( center, worldCenter );
            DirectionType dir = directions->at(i);

            if (dir.magnitude()<m_SizeThreshold)
                continue;
            if (m_NormalizeVectors)
                dir.normalize();
            count++;

            if (m_CreateDirectionImages && i<10)
            {
                if (i==m_DirectionImageContainer->size())
                {
                    ItkDirectionImageType::Pointer directionImage = ItkDirectionImageType::New();
                    directionImage->SetSpacing( spacing );
                    directionImage->SetOrigin( origin );
                    directionImage->SetDirection( direction );
                    directionImage->SetRegions( imageRegion );
                    directionImage->Allocate();
                    Vector< float, 3 > nullVec; nullVec.Fill(0.0);
                    directionImage->FillBuffer(nullVec);
                    m_DirectionImageContainer->InsertElement(i, directionImage);
                }

                // set direction image pixel
                ItkDirectionImageType::Pointer directionImage = m_DirectionImageContainer->GetElement(i);
                Vector< float, 3 > pixel;
                pixel.SetElement(0, dir[0]);
                pixel.SetElement(1, dir[1]);
                pixel.SetElement(2, dir[2]);
                directionImage->SetPixel(index, pixel);
            }

            // add direction to vector field (with spacing compensation)
            itk::Point<double> worldStart;
            worldStart[0] = worldCenter[0]-dir[0]/2*minSpacing;
            worldStart[1] = worldCenter[1]-dir[1]/2*minSpacing;
            worldStart[2] = worldCenter[2]-dir[2]/2*minSpacing;
            vtkIdType id = m_VtkPoints->InsertNextPoint(worldStart.GetDataPointer());
            container->GetPointIds()->InsertNextId(id);
            itk::Point<double> worldEnd;
            worldEnd[0] = worldCenter[0]+dir[0]/2*minSpacing;
            worldEnd[1] = worldCenter[1]+dir[1]/2*minSpacing;
            worldEnd[2] = worldCenter[2]+dir[2]/2*minSpacing;
            id = m_VtkPoints->InsertNextPoint(worldEnd.GetDataPointer());
            container->GetPointIds()->InsertNextId(id);
            m_VtkCellArray->InsertNextCell(container);
        }
        dirIt.Set(count);
        ++dirIt;
    }

    vtkSmartPointer<vtkPolyData> directionsPolyData = vtkSmartPointer<vtkPolyData>::New();
    directionsPolyData->SetPoints(m_VtkPoints);
    directionsPolyData->SetLines(m_VtkCellArray);
    m_OutputFiberBundle = mitk::FiberBundle::New(directionsPolyData);
}