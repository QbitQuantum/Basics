/** Reads in a XML file and converts it into a XMLNode tree.
 *  \param filename Name of the XML file to read.
 */
XMLNode *FileManager::createXMLTree(const std::string &filename)
{
    io::IXMLReader *xml_reader = createXMLReader(filename);
    if(!xml_reader) return NULL;
    return new XMLNode(xml_reader);
}   // getXMLTree