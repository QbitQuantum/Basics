void transformsChain::runTransform(
            const ptr<image>& inputImage,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            const ptr<image>& outputImage,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY)
{
	if(isEmpty())
	{
		ptr<transformHighBit> highBit(new transformHighBit);
		highBit->runTransform(inputImage, inputTopLeftX, inputTopLeftY, inputWidth, inputHeight, outputImage, outputTopLeftX, outputTopLeftY);
		return;
	}

	if(m_transformsList.size() == 1)
	{
		m_transformsList.front()->runTransform(inputImage, inputTopLeftX, inputTopLeftY, inputWidth, inputHeight,
			outputImage, outputTopLeftX, outputTopLeftY);
		return;
	}

	// Get the position of the last transform
	///////////////////////////////////////////////////////////
	tTransformsList::iterator lastTransform(m_transformsList.end());
	--lastTransform;

	std::wstring inputColorSpace(inputImage->getColorSpace());
	image::bitDepth inputDepth(inputImage->getDepth());
	std::uint32_t inputHighBit(inputImage->getHighBit());
	std::wstring outputColorSpace(outputImage->getColorSpace());
	image::bitDepth outputDepth(outputImage->getDepth());
	std::uint32_t outputHighBit(outputImage->getHighBit());
	std::uint32_t allocateRows = 65536 / inputWidth;
	if(allocateRows < 1)
	{
		allocateRows = 1;
	}
	if(allocateRows > inputHeight)
	{
		allocateRows = inputHeight;
	}

	// Allocate temporary images
	///////////////////////////////////////////////////////////
	if(
		m_inputWidth != inputWidth ||
		m_inputHeight != inputHeight ||
		m_inputColorSpace != inputColorSpace ||
		m_inputDepth != inputDepth ||
		m_inputHighBit != inputHighBit ||
		m_outputColorSpace != outputColorSpace ||
		m_outputDepth != outputDepth ||
		m_outputHighBit != outputHighBit)
	{
		m_inputWidth = inputWidth;
		m_inputHeight = inputHeight;
		m_inputColorSpace = inputColorSpace;
		m_inputDepth = inputDepth;
		m_inputHighBit = inputHighBit;
		m_outputColorSpace = outputColorSpace;
		m_outputDepth = outputDepth;
		m_outputHighBit = outputHighBit;

		m_temporaryImages.clear();
		tTransformsList::iterator scanTransforms(m_transformsList.begin());
		m_temporaryImages.push_back((*scanTransforms)->allocateOutputImage(inputImage, inputWidth, allocateRows));
		while(++scanTransforms != lastTransform)
		{
			m_temporaryImages.push_back((*scanTransforms)->allocateOutputImage(m_temporaryImages.back(), inputWidth, allocateRows));
		}
	}

	// Run all the transforms. Split the images into several
	//  parts
	///////////////////////////////////////////////////////////
	while(inputHeight != 0)
	{
		std::uint32_t rows = allocateRows;
		if(rows > inputHeight)
		{
			rows = inputHeight;
		}
		inputHeight -= rows;
		
		tTransformsList::iterator scanTransforms(m_transformsList.begin());
		tTemporaryImagesList::iterator scanTemporaryImages(m_temporaryImages.begin());
		
		(*scanTransforms)->runTransform(inputImage, inputTopLeftX, inputTopLeftY, inputWidth, rows, *scanTemporaryImages, 0, 0);
		inputTopLeftY += rows;

		while(++scanTransforms != lastTransform)
		{
			ptr<image> temporaryInput(*(scanTemporaryImages++));
			ptr<image> temporaryOutput(*scanTemporaryImages);

			(*scanTransforms)->runTransform(temporaryInput, 0, 0, inputWidth, rows, temporaryOutput, 0, 0);
		}

		m_transformsList.back()->runTransform(*scanTemporaryImages, 0, 0, inputWidth, rows, outputImage, outputTopLeftX, outputTopLeftY);
		outputTopLeftY += rows;
	}
}