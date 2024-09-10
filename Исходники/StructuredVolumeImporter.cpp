void StructuredVolumeImporter::import( const kvs::DicomList* dicom_list )
{
    if ( dicom_list->size() == 0 )
    {
        BaseClass::setSuccess( false );
        kvsMessageError("Dicom file is not included.");
        return;
    }

    const float spacing = static_cast<float>( dicom_list->sliceSpacing() );
    const float thickness = static_cast<float>( dicom_list->sliceThickness() );

    const size_t x_size = dicom_list->width();
    const size_t y_size = dicom_list->height();
    const size_t z_size = dicom_list->nslices();
    const float x_ratio = dicom_list->pixelSpacing()[0];
    const float y_ratio = dicom_list->pixelSpacing()[1];
    const float z_ratio = kvs::Math::IsZero( spacing ) ? kvs::Math::IsZero( thickness ) ? x_ratio : thickness : spacing;

    const kvs::Vector3f min_obj_coord( 0.0f, 0.0f, 0.0f );
    const kvs::Vector3f max_obj_coord( x_size - 1.0f, y_size - 1.0f, z_size - 1.0f );
    SuperClass::setMinMaxObjectCoords( min_obj_coord, max_obj_coord );

    const kvs::Vector3f min_ext_coord( min_obj_coord );
    const kvs::Vector3f max_ext_coord( max_obj_coord.x() * x_ratio,
                                       max_obj_coord.y() * y_ratio,
                                       max_obj_coord.z() * z_ratio );
    SuperClass::setMinMaxExternalCoords( min_ext_coord, max_ext_coord );

    bool shift = true;
    const kvs::Dicom* dicom = (*dicom_list)[0];
    const kvs::UInt32 bits_allocated = dicom->bitsAllocated();
    const bool pixel_representation = dicom->pixelRepresentation();
    switch ( bits_allocated )
    {
    case 8:
    {
        const kvs::AnyValueArray values = this->get_dicom_data<kvs::UInt8>( dicom_list, false );
        SuperClass::setValues( values );
        break;
    }
    case 16:
    {
        if ( pixel_representation )
        {
            const kvs::AnyValueArray values = this->get_dicom_data<kvs::UInt16>( dicom_list, false );
            SuperClass::setValues( values );
        }
        else
        {
            if ( shift )
            {
                const kvs::AnyValueArray values = this->get_dicom_data<kvs::UInt16>( dicom_list, true );
                SuperClass::setValues( values );
            }
            else
            {
                const kvs::AnyValueArray values = this->get_dicom_data<kvs::Int16>( dicom_list, false );
                SuperClass::setValues( values );
            }
        }
        break;
    }
    default: break;
    }

    const kvs::Vector3ui resolution( x_size, y_size, z_size );
    SuperClass::setGridType( kvs::StructuredVolumeObject::Uniform );
    SuperClass::setResolution( resolution );
    SuperClass::setVeclen( 1 );
    SuperClass::updateMinMaxValues();
}