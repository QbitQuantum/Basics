osgDB::ReaderWriter::WriteResult
ReaderWriterIV::writeNode(const osg::Node& node, const std::string& fileName,
                          const osgDB::ReaderWriter::Options* /*options*/) const
{
    // accept extension
    std::string ext = osgDB::getLowerCaseFileExtension(fileName);
    if (!acceptsExtension(ext)) return WriteResult::FILE_NOT_HANDLED;
    bool useVRML1 = !isInventorExtension(osgDB::getFileExtension(fileName));

    OSG_NOTICE << "osgDB::ReaderWriterIV::writeNode() Writing file "
                             << fileName.data() << std::endl;

    // Convert OSG graph to Inventor graph
    ConvertToInventor osg2iv;
    osg2iv.setVRML1Conversion(useVRML1);
    (const_cast<osg::Node*>(&node))->accept(osg2iv);
    SoNode *ivRoot = osg2iv.getIvSceneGraph();
    if (ivRoot == NULL)
        return WriteResult::ERROR_IN_WRITING_FILE;
    ivRoot->ref();

    // Change prefix according to VRML spec:
    // Node names must not begin with a digit, and must not contain spaces or
    // control characters, single or double quote characters, backslashes, curly braces,
    // the sharp (#) character, the plus (+) character or the period character.
    if (useVRML1)
      SoBase::setInstancePrefix("_");

    // Write Inventor graph to file
    SoOutput out;
    out.setHeaderString((useVRML1) ? "#VRML V1.0 ascii" : "#Inventor V2.1 ascii");
    if (!out.openFile(fileName.c_str()))
        return WriteResult::ERROR_IN_WRITING_FILE;
    SoWriteAction wa(&out);
    wa.apply(ivRoot);
    ivRoot->unref();

    return WriteResult::FILE_SAVED;
}