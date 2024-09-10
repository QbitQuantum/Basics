int testRepresenterForVectorImage(const std::string& datadir) {

    typedef itk::StandardImageRepresenter<itk::Vector<float, 2>, 2> RepresenterType;
    typedef GenericRepresenterTest<RepresenterType> RepresenterTestType;

    const std::string referenceFilename = datadir + "/hand_dfs/df-hand-1.vtk";
    const std::string testDatasetFilename = datadir + "/hand_dfs/df-hand-2.vtk";

    RepresenterType::Pointer representer = RepresenterType::New();
    VectorImageType::Pointer reference = loadVectorImage(referenceFilename);
    representer->SetReference(reference);

    // choose a test dataset, a point and its associate pixel value

    VectorImageType::Pointer testDataset = loadVectorImage(testDatasetFilename);
    VectorImageType::IndexType idx;
    idx.Fill(0);
    VectorImageType::PointType testPt;
    reference->TransformIndexToPhysicalPoint(idx, testPt);
    VectorImageType::PixelType testValue = testDataset->GetPixel(idx);

    RepresenterTestType representerTest(representer, testDataset, std::make_pair(testPt, testValue));

    return (representerTest.runAllTests() == true);
}