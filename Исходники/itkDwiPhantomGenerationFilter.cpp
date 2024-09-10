void DwiPhantomGenerationFilter< TOutputScalarType >
::GenerateData()
{
    if (m_NoiseVariance < 0)
        m_NoiseVariance = 0.001;

    if (!m_SimulateBaseline)
    {
        MITK_INFO << "Baseline image values are set to default. Noise variance value is treated as SNR!";
        if (m_NoiseVariance <= 0)
            m_NoiseVariance = 0.0001;
        if (m_NoiseVariance>99)
            m_NoiseVariance = 0;
        else
        {
            m_NoiseVariance = m_DefaultBaseline/(m_NoiseVariance*m_SignalScale);
            m_NoiseVariance *= m_NoiseVariance;
        }
    }

    m_RandGen = Statistics::MersenneTwisterRandomVariateGenerator::New();
    m_RandGen->SetSeed();

    typename OutputImageType::Pointer outImage = OutputImageType::New();
    outImage->SetSpacing( m_Spacing );
    outImage->SetOrigin( m_Origin );
    outImage->SetDirection( m_DirectionMatrix );
    outImage->SetLargestPossibleRegion( m_ImageRegion );
    outImage->SetBufferedRegion( m_ImageRegion );
    outImage->SetRequestedRegion( m_ImageRegion );
    outImage->SetVectorLength(m_GradientList.size());
    outImage->Allocate();
    typename OutputImageType::PixelType pix;
    pix.SetSize(m_GradientList.size());
    pix.Fill(0.0);
    outImage->FillBuffer(pix);
    this->SetNthOutput (0, outImage);

    double minSpacing = m_Spacing[0];
    if (m_Spacing[1]<minSpacing)
        minSpacing = m_Spacing[1];
    if (m_Spacing[2]<minSpacing)
        minSpacing = m_Spacing[2];

    m_DirectionImageContainer = ItkDirectionImageContainer::New();
    for (int i=0; i<m_SignalRegions.size(); i++)
    {
        itk::Vector< float, 3 > nullVec; nullVec.Fill(0.0);
        ItkDirectionImage::Pointer img = ItkDirectionImage::New();
        img->SetSpacing( m_Spacing );
        img->SetOrigin( m_Origin );
        img->SetDirection( m_DirectionMatrix );
        img->SetRegions( m_ImageRegion );
        img->Allocate();
        img->FillBuffer(nullVec);
        m_DirectionImageContainer->InsertElement(m_DirectionImageContainer->Size(), img);
    }
    m_NumDirectionsImage = ItkUcharImgType::New();
    m_NumDirectionsImage->SetSpacing( m_Spacing );
    m_NumDirectionsImage->SetOrigin( m_Origin );
    m_NumDirectionsImage->SetDirection( m_DirectionMatrix );
    m_NumDirectionsImage->SetRegions( m_ImageRegion );
    m_NumDirectionsImage->Allocate();
    m_NumDirectionsImage->FillBuffer(0);

    m_SNRImage = ItkFloatImgType::New();
    m_SNRImage->SetSpacing( m_Spacing );
    m_SNRImage->SetOrigin( m_Origin );
    m_SNRImage->SetDirection( m_DirectionMatrix );
    m_SNRImage->SetRegions( m_ImageRegion );
    m_SNRImage->Allocate();
    m_SNRImage->FillBuffer(0);

    vtkSmartPointer<vtkCellArray> m_VtkCellArray = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkPoints>    m_VtkPoints = vtkSmartPointer<vtkPoints>::New();

    m_BaselineImages = 0;
    for( unsigned int i=0; i<m_GradientList.size(); i++)
        if (m_GradientList[i].GetNorm()<=0.0001)
            m_BaselineImages++;

    typedef ImageRegionIterator<OutputImageType>      IteratorOutputType;
    IteratorOutputType it (outImage, m_ImageRegion);

    // isotropic tensor
    itk::DiffusionTensor3D<float> isoTensor;
    isoTensor.Fill(0);
    float e1 = m_GreyMatterAdc;
    float e2 = m_GreyMatterAdc;
    float e3 = m_GreyMatterAdc;
    isoTensor.SetElement(0,e1);
    isoTensor.SetElement(3,e2);
    isoTensor.SetElement(5,e3);
    m_MaxBaseline = GetTensorL2Norm(isoTensor);

    GenerateTensors();

    // simulate measurement
    m_MeanBaseline = 0;
    double noiseStdev = sqrt(m_NoiseVariance);
    while(!it.IsAtEnd())
    {
        pix = it.Get();
        typename OutputImageType::IndexType index = it.GetIndex();

        int numDirs = 0;
        for (int i=0; i<m_SignalRegions.size(); i++)
        {
            ItkUcharImgType::Pointer region = m_SignalRegions.at(i);

            if (region->GetPixel(index)!=0)
            {
                numDirs++;
                pix += SimulateMeasurement(m_TensorList[i], m_TensorWeight[i]);

                // set direction image pixel
                ItkDirectionImage::Pointer img = m_DirectionImageContainer->GetElement(i);
                itk::Vector< float, 3 > pixel = img->GetPixel(index);
                vnl_vector_fixed<double, 3> dir = m_TensorDirection.at(i);
                dir.normalize();
                dir *= m_TensorWeight.at(i);
                pixel.SetElement(0, dir[0]);
                pixel.SetElement(1, dir[1]);
                pixel.SetElement(2, dir[2]);
                img->SetPixel(index, pixel);

                vtkSmartPointer<vtkPolyLine> container = vtkSmartPointer<vtkPolyLine>::New();
                itk::ContinuousIndex<double, 3> center;
                center[0] = index[0];
                center[1] = index[1];
                center[2] = index[2];
                itk::Point<double> worldCenter;
                outImage->TransformContinuousIndexToPhysicalPoint( center, worldCenter );
                itk::Point<double> worldStart;
                worldStart[0] = worldCenter[0]-dir[0]/2 * minSpacing;
                worldStart[1] = worldCenter[1]-dir[1]/2 * minSpacing;
                worldStart[2] = worldCenter[2]-dir[2]/2 * minSpacing;
                vtkIdType id = m_VtkPoints->InsertNextPoint(worldStart.GetDataPointer());
                container->GetPointIds()->InsertNextId(id);
                itk::Point<double> worldEnd;
                worldEnd[0] = worldCenter[0]+dir[0]/2 * minSpacing;
                worldEnd[1] = worldCenter[1]+dir[1]/2 * minSpacing;
                worldEnd[2] = worldCenter[2]+dir[2]/2 * minSpacing;
                id = m_VtkPoints->InsertNextPoint(worldEnd.GetDataPointer());
                container->GetPointIds()->InsertNextId(id);
                m_VtkCellArray->InsertNextCell(container);
            }
        }

        if (numDirs>1)
        {
            for (int i=0; i<m_GradientList.size(); i++)
                pix[i] /= numDirs;
        }
        else if (numDirs==0)
        {
            if (m_SimulateBaseline)
                pix = SimulateMeasurement(isoTensor, 1.0);
            else
                pix.Fill(0.0);
        }

        m_MeanBaseline += pix[0];
        it.Set(pix);
        m_NumDirectionsImage->SetPixel(index, numDirs);
        if (m_NoiseVariance>0)
            m_SNRImage->SetPixel(index, pix[0]/(noiseStdev*m_SignalScale));
        ++it;
    }
    m_MeanBaseline /= m_ImageRegion.GetNumberOfPixels();
    if (m_NoiseVariance>0)
        MITK_INFO << "Mean SNR: " << m_MeanBaseline/(noiseStdev*m_SignalScale);
    else
        MITK_INFO << "No noise added";

    // add rician noise
    it.GoToBegin();
    while(!it.IsAtEnd())
    {
        pix = it.Get();
        AddNoise(pix);
        it.Set(pix);
        ++it;
    }

    // generate fiber bundle
    vtkSmartPointer<vtkPolyData> directionsPolyData = vtkSmartPointer<vtkPolyData>::New();
    directionsPolyData->SetPoints(m_VtkPoints);
    directionsPolyData->SetLines(m_VtkCellArray);
    m_OutputFiberBundle = mitk::FiberBundleX::New(directionsPolyData);
}