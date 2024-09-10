TEST_F(STEMPluginTest, DISABLED_PreFilterResidualsDetermineDeltaR)
{
    auto tempImage = ImageDeserializer::readImage(testdataDirectory + "adjoint/testdata_realworld.tif");
    GPUMapped<Image>* image = new GPUMapped<Image>(framework->getOpenCLStack(), tempImage);
    ImageSerializer::writeImage(workDirectory + "adjoint/testdata_output", image, ImageSerializer::TIFF_GRAY_32);

    PrefilterOperator* preFilter = new PrefilterOperator(framework, image, 10.0f);

    preFilter->run();

    preFilter->getOutput()->ensureIsUpToDateOnCPU();
    Image* preFilteredImage = preFilter->getOutput()->getObjectOnCPU();

    unsigned int nSamples = 100;
    std::ofstream ofs(workDirectory + "adjoint/determine_delta_r.csv", std::ios::out);
    ofs << "x;y;";
    for(unsigned int i = 0; i < nSamples; i++)
        ofs << "value" << i << ";";
    ofs << "totalError" << std::endl;

    std::vector<Vec2ui> samplePositions;
    RandomAlgorithms::generateRandomPointsFromZeroToMax(100, image->getResolution(), samplePositions);
    for(unsigned int i = 0; i < nSamples; i++)
    {
        Vec2ui samplePosition = samplePositions[i];
        ofs << samplePosition.x << ";" << samplePosition.y << ";";
        float totalError = 0.0f;
        for(unsigned int z = 1; z < preFilter->NumberOfSamplingSteps() - 1; z++)
        {
            float value0 = preFilteredImage->getPixel(samplePosition.x, samplePosition.y + (z - 1) * image->getResolution().y);
            float value1 = preFilteredImage->getPixel(samplePosition.x, samplePosition.y + (z)* image->getResolution().y);
            float value2 = preFilteredImage->getPixel(samplePosition.x, samplePosition.y + (z + 1) * image->getResolution().y);
            float theoreticValue = (value2 + value0) / 2.0f;
            float error = fabs(value1 - theoreticValue);
            ofs << value1 << ";";
            totalError += error;
        }
        ofs << totalError << std::endl;
    }
    ofs.close();

    ImageSerializer::writeImage(workDirectory + "adjoint/prefiltered_residuals_determine_delta_r", preFilter->getOutput(), ImageSerializer::TIFF_GRAY_32);

    delete preFilter;

    ettention::ImageComparator::assertImagesAreEqual(workDirectory + "adjoint/prefiltered_residuals.tif", testdataDirectory + "adjoint/prefiltered_residuals.tif");
    delete image;
    delete tempImage;
}