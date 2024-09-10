  mitk::TbssImage::Pointer mitk::TbssImporter::ImportMeta()
  {
    mitk::TbssImage::Pointer tbssImg = mitk::TbssImage::New();

    m_Data = DataImageType::New();

    std::vector< std::pair<mitk::TbssImage::MetaDataFunction, int> > metaInfo;

    // Gradient images are vector images, so they will add more dimensions to the vector
    int vecLength = m_MetaFiles.size();
    //Check if there is a gradient image

    for(int i=0; i < m_MetaFiles.size(); i++)
    {
      std::pair<std::string, std::string> p = m_MetaFiles.at(i);
      if(RetrieveTbssFunction(p.first) == mitk::TbssImage::GRADIENT_X)
      {
        vecLength += 2;
      }
    }


    int currIndex = 0;


    for(int i=0; i < m_MetaFiles.size(); i++)
    {
      std::pair<std::string, std::string> p = m_MetaFiles.at(i);
      std::string function = p.first;
      std::string file = p.second;

      // Add to metainfo to give the tbss image a function-index pair
      std::pair<mitk::TbssImage::MetaDataFunction, int> pair;


      pair.first = RetrieveTbssFunction(function);
      pair.second = i;

      if(pair.first == mitk::TbssImage::GRADIENT_X)
      {
        metaInfo.push_back(std::pair<mitk::TbssImage::MetaDataFunction, int>(mitk::TbssImage::GRADIENT_X, i));
        metaInfo.push_back(std::pair<mitk::TbssImage::MetaDataFunction, int>(mitk::TbssImage::GRADIENT_Y, i+1));
        metaInfo.push_back(std::pair<mitk::TbssImage::MetaDataFunction, int>(mitk::TbssImage::GRADIENT_Z, i+2));


        VectorReaderType::Pointer fileReader = VectorReaderType::New();
        fileReader->SetFileName(file);
        itk::NrrdImageIO::Pointer io = itk::NrrdImageIO::New();
        fileReader->SetImageIO(io);
        fileReader->Update();

        VectorImageType::Pointer img = fileReader->GetOutput();

        VectorImageType::SizeType size = img->GetLargestPossibleRegion().GetSize();

        if(i==0)
        {
          // First image in serie. Properties should be used to initialize m_Data
          m_Data->SetRegions(img->GetLargestPossibleRegion().GetSize());
          m_Data->SetSpacing(img->GetSpacing());
          m_Data->SetOrigin(img->GetOrigin());
          m_Data->SetDirection(img->GetDirection());
          m_Data->SetVectorLength(vecLength);
          m_Data->Allocate();
        }


        /* Dealing with a gradient image, so the size of the vector need to be increased by 2
            since this image contains 3 volumes. Old data should not be deleted*/



        for(int x=0; x<size[0]; x++)
        {
          for(int y=0; y<size[1]; y++)
          {
            for(int z=0; z<size[2]; z++)
            {
              itk::Index<3> ix;
              ix[0] = x;
              ix[1] = y;
              ix[2] = z;

              itk::VariableLengthVector<int> vec = img->GetPixel(ix);
              itk::VariableLengthVector<float> pixel = m_Data->GetPixel(ix);
              for(int j=0; j<vec.Size(); j++)
              {
                int pos = currIndex+j;
                float f = vec.GetElement(j);
                pixel.SetElement(pos, f);

              }
              m_Data->SetPixel(ix, pixel);
            }
          }
        }

        currIndex += img->GetVectorLength();
        tbssImg->SetContainsGradient(true);
        // Read vector image and add to m_Data
      }

      else {

        metaInfo.push_back(pair);
        FileReaderType3D::Pointer fileReader = FileReaderType3D::New();
        fileReader->SetFileName(file);
        fileReader->Update();

        FloatImage3DType::Pointer img = fileReader->GetOutput();

        FloatImage3DType::SizeType size = img->GetLargestPossibleRegion().GetSize();

        if(i==0)
        {
          // First image in serie. Properties should be used to initialize m_Data
          m_Data->SetRegions(img->GetLargestPossibleRegion().GetSize());
          m_Data->SetSpacing(img->GetSpacing());
          m_Data->SetOrigin(img->GetOrigin());
          m_Data->SetDirection(img->GetDirection());
          m_Data->SetVectorLength(vecLength);         
          m_Data->Allocate();
        }

        for(int x=0; x<size[0]; x++)
        {
          for(int y=0; y<size[1]; y++)
          {
            for(int z=0; z<size[2]; z++)
            {
              itk::Index<3> ix;
              ix[0] = x;
              ix[1] = y;
              ix[2] = z;

              float f = img->GetPixel(ix);
              itk::VariableLengthVector<float> pixel = m_Data->GetPixel(ix);
              pixel.SetElement(currIndex, f);
              m_Data->SetPixel(ix, pixel);

            }
          }
        }
      }

      if(pair.first == mitk::TbssImage::MEAN_FA_SKELETON)
      {
        tbssImg->SetContainsMeanSkeleton(true);
      }
      else if(pair.first == mitk::TbssImage::MEAN_FA_SKELETON_MASK)
      {
        tbssImg->SetContainsSkeletonMask(true);
      }
      else if(pair.first == mitk::TbssImage::DISTANCE_MAP)
      {
        tbssImg->SetContainsDistanceMap(true);
      }

      currIndex++;

    }

    tbssImg->SetIsMeta(true);
    tbssImg->SetImage(m_Data);
    tbssImg->SetMetaInfo(metaInfo);
    tbssImg->InitializeFromVectorImage();

    return tbssImg;
  }