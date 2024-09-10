void mitk::PlanarFigureWriter::GenerateData()
{
  m_Success = false;

  if (!m_WriteToMemory && m_FileName.empty())
  {
    MITK_ERROR << "Could not write planar figures. File name is invalid";
    throw std::invalid_argument("file name is empty");
  }

  TiXmlDocument document;
  auto  decl = new TiXmlDeclaration( "1.0", "", "" ); // TODO what to write here? encoding? etc....
  document.LinkEndChild( decl );

  auto  version = new TiXmlElement("Version");
  version->SetAttribute("Writer",  __FILE__ );
  version->SetAttribute("CVSRevision",  "$Revision: 17055 $" );
  version->SetAttribute("FileVersion",  1 );
  document.LinkEndChild(version);


  /* create xml element for each input */
  for ( unsigned int i = 0 ; i < this->GetNumberOfInputs(); ++i )
  {
    // Create root element for this PlanarFigure
    InputType::Pointer pf = this->GetInput( i );
    if (pf.IsNull())
      continue;
    auto  pfElement = new TiXmlElement("PlanarFigure");
    pfElement->SetAttribute("type", pf->GetNameOfClass());
    document.LinkEndChild(pfElement);

    if ( pf->GetNumberOfControlPoints() == 0 )
      continue;

    //PlanarFigure::VertexContainerType* vertices = pf->GetControlPoints();
    //if (vertices == NULL)
    //  continue;

    // Serialize property list of PlanarFigure
    mitk::PropertyList::Pointer propertyList = pf->GetPropertyList();
    mitk::PropertyList::PropertyMap::const_iterator it;
    for ( it = propertyList->GetMap()->begin(); it != propertyList->GetMap()->end(); ++it )
    {
      // Create seralizer for this property
      const mitk::BaseProperty* prop = it->second;
      std::string serializerName = std::string( prop->GetNameOfClass() ) + "Serializer";
      std::list< itk::LightObject::Pointer > allSerializers = itk::ObjectFactoryBase::CreateAllInstance(
        serializerName.c_str() );

      if ( allSerializers.size() != 1 )
      {
        // No or too many serializer(s) found, skip this property
        continue;
      }

      mitk::BasePropertySerializer* serializer = dynamic_cast< mitk::BasePropertySerializer* >(
        allSerializers.begin()->GetPointer() );
      if ( serializer == nullptr )
      {
        // Serializer not valid; skip this property
      }

      auto  keyElement = new TiXmlElement( "property" );
      keyElement->SetAttribute( "key", it->first );
      keyElement->SetAttribute( "type", prop->GetNameOfClass() );

        serializer->SetProperty( prop );
      TiXmlElement* valueElement = nullptr;
      try
      {
        valueElement = serializer->Serialize();
      }
      catch (...)
      {
      }

      if ( valueElement == nullptr )
      {
        // Serialization failed; skip this property
        continue;
      }

      // Add value to property element
      keyElement->LinkEndChild( valueElement );

      // Append serialized property to property list
      pfElement->LinkEndChild( keyElement );
    }

    // Serialize control points of PlanarFigure
    auto  controlPointsElement = new TiXmlElement("ControlPoints");
    pfElement->LinkEndChild(controlPointsElement);
    for (unsigned int i = 0; i < pf->GetNumberOfControlPoints(); i++)
    {
      auto  vElement = new TiXmlElement("Vertex");
      vElement->SetAttribute("id", i);
      vElement->SetDoubleAttribute("x", pf->GetControlPoint(i)[0]);
      vElement->SetDoubleAttribute("y", pf->GetControlPoint(i)[1]);
      controlPointsElement->LinkEndChild(vElement);
    }
    auto  geoElement = new TiXmlElement("Geometry");
    const PlaneGeometry* planeGeo = dynamic_cast<const PlaneGeometry*>(pf->GetPlaneGeometry());
    if (planeGeo != nullptr)
    {
      // Write parameters of IndexToWorldTransform of the PlaneGeometry
      typedef mitk::Geometry3D::TransformType TransformType;
      const TransformType* affineGeometry = planeGeo->GetIndexToWorldTransform();
      const TransformType::ParametersType& parameters = affineGeometry->GetParameters();
      auto  vElement = new TiXmlElement( "transformParam" );
      for ( unsigned int i = 0; i < affineGeometry->GetNumberOfParameters(); ++i )
      {
        std::stringstream paramName;
        paramName << "param" << i;
        vElement->SetDoubleAttribute( paramName.str().c_str(), parameters.GetElement( i ) );
      }
      geoElement->LinkEndChild( vElement );

      // Write bounds of the PlaneGeometry
      typedef mitk::Geometry3D::BoundsArrayType BoundsArrayType;
      const BoundsArrayType& bounds = planeGeo->GetBounds();
      vElement = new TiXmlElement( "boundsParam" );
      for ( unsigned int i = 0; i < 6; ++i )
      {
        std::stringstream boundName;
        boundName << "bound" << i;
        vElement->SetDoubleAttribute( boundName.str().c_str(), bounds.GetElement( i ) );
      }
      geoElement->LinkEndChild( vElement );

      // Write spacing and origin of the PlaneGeometry
      Vector3D spacing = planeGeo->GetSpacing();
      Point3D origin = planeGeo->GetOrigin();
      geoElement->LinkEndChild(this->CreateXMLVectorElement("Spacing", spacing));
      geoElement->LinkEndChild(this->CreateXMLVectorElement("Origin", origin));

      pfElement->LinkEndChild(geoElement);
    }
  }


  if(m_WriteToMemory)
  {
    // Declare a printer
    TiXmlPrinter printer;
    // attach it to the document you want to convert in to a std::string
    document.Accept(&printer);

    // Create memory buffer and print tinyxmldocument there...
    m_MemoryBufferSize  = printer.Size() + 1;
    m_MemoryBuffer      = new char[m_MemoryBufferSize];
    strcpy(m_MemoryBuffer,printer.CStr());
  }
  else
  {
    if (document.SaveFile( m_FileName) == false)
    {
      MITK_ERROR << "Could not write planar figures to " << m_FileName << "\nTinyXML reports '" << document.ErrorDesc() << "'";
      throw std::ios_base::failure("Error during writing of planar figure xml file.");
    }
  }
  m_Success = true;
}