/// \brief this function takes a path to some IGES file and returns an OpenSceneGraph Geode
///        which directly can be used anywhere. It calculates normals using osgUtil::smoother
osg::ref_ptr<osg::Geode> igesToOSGGeode(const std::string& filePath)
{
    // XDE: Extended Data Exchange
    // OCAF: OpenCascade Application Technology Framework
    /// Getting an XDE document
    Handle(TDocStd_Document) doc;
    XCAFApp_Application::GetApplication()->NewDocument("MDTV-XCAF", doc);

    IGESCAFControl_Reader reader; 
    reader.SetColorMode(true);
    reader.SetNameMode(true);
    reader.SetLayerMode(true);

    //IGESControl_Reader Reader;
    reader.ReadFile( (Standard_CString)filePath.c_str() );
    /// transfer data from reader to doc
    if(!reader.Transfer(doc))
    {
        cout << "Cannot read any relevant data from the IGES file" << endl;
        return NULL;
    }

    BRepConverter brepConverter;
    return brepConverter.brepToOSGGeode(*doc);
}