CC_FILE_ERROR LASFilter::saveToFile(ccHObject* entity, const char* filename)
{
   if (!entity || !filename)
      return CC_FERR_BAD_ARGUMENT;

   ccHObject::Container clouds;
   if (entity->isKindOf(CC_POINT_CLOUD))
      clouds.push_back(entity);
   else
      entity->filterChildren(clouds, true, CC_POINT_CLOUD);

   if (clouds.empty())
   {
      ccConsole::Error("No point cloud in input selection!");
      return CC_FERR_BAD_ENTITY_TYPE;
   }
   else if (clouds.size()>1)
   {
      ccConsole::Error("Can't save more than one cloud per LAS file!");
      return CC_FERR_BAD_ENTITY_TYPE;
   }

   //the cloud to save
   ccGenericPointCloud* theCloud = static_cast<ccGenericPointCloud*>(clouds[0]);
   unsigned numberOfPoints = theCloud->size();

   if (numberOfPoints==0)
   {
      ccConsole::Error("Cloud is empty!");
      return CC_FERR_BAD_ENTITY_TYPE;
   }

   //colors
   bool hasColor = theCloud->hasColors();

   //classification (as a scalar field)
   CCLib::ScalarField* classifSF = 0;
   if (theCloud->isA(CC_POINT_CLOUD))
   {
      ccPointCloud* pc = static_cast<ccPointCloud*>(theCloud);
      int sfIdx = pc->getScalarFieldIndexByName(CC_LAS_CLASSIFICATION_FIELD_NAME);
      if (sfIdx>=0)
      {
         classifSF = pc->getScalarField(sfIdx);
         if (/*classifSF->getMax()>(ScalarType)liblas::Classification::class_table_size ||*/ classifSF->getMin()<0)
         {
            ccConsole::Warning("[LASFilter] Found a 'classification' scalar field, but its values outbounds LAS specifications (0-255)...");
            classifSF = 0;
         }
         else
         {
            //we check that it's only integer values!
            unsigned i,count=classifSF->currentSize();
            classifSF->placeIteratorAtBegining();
            double integerPart = 0.0;
            for (i=0;i<count;++i)
            {
               if (modf(classifSF->getCurrentValue(),&integerPart) != 0.0)
               {
                  ccConsole::Warning("[LASFilter] Found a 'classification' scalar field, but its values are not pure integers...");
                  classifSF = 0;
                  break;
               }
            }
         }
      }
   }

   //open binary file for writing
   std::ofstream ofs;
   ofs.open(filename, std::ios::out | std::ios::binary);

   if (ofs.fail())
      return CC_FERR_WRITING;

   const double* shift = theCloud->getOriginalShift();

   liblas::Writer* writer = 0;
   try
   {
      liblas::Header header;

      //LAZ support based on extension!
      if (QFileInfo(filename).suffix().toUpper() == "LAZ")
      {
         header.SetCompressed(true);
      }

      //header.SetDataFormatId(liblas::ePointFormat3);
      ccBBox bBox = theCloud->getBB();
      if (bBox.isValid())
      {
         header.SetMin(-shift[0]+(double)bBox.minCorner().x,-shift[1]+(double)bBox.minCorner().y,-shift[2]+(double)bBox.minCorner().z);
         header.SetMax(-shift[0]+(double)bBox.maxCorner().x,-shift[1]+(double)bBox.maxCorner().y,-shift[2]+(double)bBox.maxCorner().z);
         CCVector3 diag = bBox.getDiagVec();

         //Set offset & scale, as points will be stored as boost::int32_t values (between 0 and 4294967296)
         //int_value = (double_value-offset)/scale
         header.SetOffset(-shift[0]+(double)bBox.minCorner().x,-shift[1]+(double)bBox.minCorner().y,-shift[2]+(double)bBox.minCorner().z);
         header.SetScale(1.0e-9*std::max<double>(diag.x,ZERO_TOLERANCE), //result must fit in 32bits?!
            1.0e-9*std::max<double>(diag.y,ZERO_TOLERANCE),
            1.0e-9*std::max<double>(diag.z,ZERO_TOLERANCE));
      }
      header.SetPointRecordsCount(numberOfPoints);
      //header.SetDataFormatId(Header::ePointFormat1);

      writer = new liblas::Writer(ofs, header);
   }
   catch (...)
   {
      return CC_FERR_WRITING;
   }

   //progress dialog
   ccProgressDialog pdlg(true); //cancel available
   CCLib::NormalizedProgress nprogress(&pdlg,numberOfPoints);
   pdlg.setMethodTitle("Save LAS file");
   char buffer[256];
   sprintf(buffer,"Points: %i",numberOfPoints);
   pdlg.setInfo(buffer);
   pdlg.start();

   //liblas::Point point(boost::shared_ptr<liblas::Header>(new liblas::Header(writer->GetHeader())));
   liblas::Point point(&writer->GetHeader());

   for (unsigned i=0; i<numberOfPoints; i++)
   {
      const CCVector3* P = theCloud->getPoint(i);
      {
         double x=-shift[0]+(double)P->x;
         double y=-shift[1]+(double)P->y;
         double z=-shift[2]+(double)P->z;
         point.SetCoordinates(x, y, z);
      }
      if (hasColor)
      {
         const colorType* rgb = theCloud->getPointColor(i);
         point.SetColor(liblas::Color(rgb[0]<<8,rgb[1]<<8,rgb[2]<<8)); //DGM: LAS colors are stored on 16 bits!
      }

      if (classifSF)
      {
         liblas::Classification classif;
         classif.SetClass((boost::uint32_t)classifSF->getValue(i));
         point.SetClassification(classif);
      }
      writer->WritePoint(point);

      if (!nprogress.oneStep())
         break;
   }

   delete writer;
   //ofs.close();

   return CC_FERR_NO_ERROR;
}