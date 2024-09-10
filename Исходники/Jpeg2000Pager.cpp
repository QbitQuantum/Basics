CachedPage::UnitPtr Jpeg2000Pager::populateImageData(const DimensionDescriptor& startRow,
                                                     const DimensionDescriptor& startColumn,
                                                     unsigned int concurrentRows, unsigned int concurrentColumns) const
{
   VERIFYRV(startRow.isOnDiskNumberValid() == true, CachedPage::UnitPtr());
   VERIFYRV(startColumn.isOnDiskNumberValid() == true, CachedPage::UnitPtr());
   VERIFYRV(concurrentRows > 0, CachedPage::UnitPtr());
   VERIFYRV(concurrentColumns > 0, CachedPage::UnitPtr());

   // Get the rows, colums, and bands to load
   unsigned int onDiskStartRow = startRow.getOnDiskNumber();
   unsigned int onDiskStopRow = onDiskStartRow + concurrentRows;
   unsigned int onDiskStartColumn = startColumn.getOnDiskNumber();
   unsigned int onDiskStopColumn = onDiskStartColumn + concurrentColumns;

   const RasterElement* pRaster = getRasterElement();
   VERIFYRV(pRaster != NULL, CachedPage::UnitPtr());

   const RasterDataDescriptor* pDescriptor = dynamic_cast<const RasterDataDescriptor*>(pRaster->getDataDescriptor());
   VERIFYRV(pDescriptor != NULL, CachedPage::UnitPtr());

   const RasterFileDescriptor* pFileDescriptor =
      dynamic_cast<const RasterFileDescriptor*>(pDescriptor->getFileDescriptor());
   VERIFYRV(pFileDescriptor != NULL, CachedPage::UnitPtr());

   const std::vector<DimensionDescriptor>& allBands = pFileDescriptor->getBands();
   if (allBands.empty() == true)
   {
      return CachedPage::UnitPtr();
   }

   // Create the output data
   unsigned int numPixels = concurrentRows * concurrentColumns * allBands.size();
   unsigned int numBytes = numPixels * getBytesPerBand();

   if (numPixels > static_cast<unsigned int>(std::numeric_limits<int>::max()))   // ArrayResource only allocates up
                                                                                 // to INT_MAX number of values
   {
      return CachedPage::UnitPtr();
   }

   ArrayResource<Out> pDestination(numPixels, true);
   char* pDest = reinterpret_cast<char*>(pDestination.get());
   if (pDest == NULL)
   {
      return CachedPage::UnitPtr();
   }

   memset(pDest, 0, numPixels);

   // Decode the image from the file, first trying the codestream format then the file format
   opj_image_t* pImage = decodeImage(onDiskStartRow, onDiskStartColumn, onDiskStopRow, onDiskStopColumn,
      Jpeg2000Utilities::J2K_CFMT);
   if (pImage == NULL)
   {
      pImage = decodeImage(onDiskStartRow, onDiskStartColumn, onDiskStopRow, onDiskStopColumn,
         Jpeg2000Utilities::JP2_CFMT);
   }

   if (pImage == NULL)
   {
      return CachedPage::UnitPtr();
   }

   // Populate the output image data
   int bandFactor = 1;

   std::string filename = pRaster->getFilename();
   if (filename.empty() == false)
   {
      QStringList parts = QString::fromStdString(filename).split('.');
      foreach (QString part, parts)
      {
         bool error;
         EncodingType dataType = StringUtilities::fromXmlString<EncodingType>(part.toStdString(), &error);
         if (dataType.isValid() == true && error == false)
         {
            int currentBandFactor = Jpeg2000Utilities::get_num_bands(dataType);
            if (currentBandFactor > 0)
            {
               bandFactor = currentBandFactor;
               break;
            }
         }
      }