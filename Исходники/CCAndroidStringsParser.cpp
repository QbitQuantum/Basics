void CCAndroidStringsParser::parse(const string& path, const CCDictionary& dict) {
    // map file path
    string localPath = CCUtils::mapLocalPath(path);
    
    // load file, if success, visit it
    XMLDocument* doc = new XMLDocument();
    if(doc->LoadFile(localPath.c_str()) == XML_NO_ERROR) {
        m_dict = (CCDictionary*)&dict;
        doc->Accept(this);
    }
    
    // release
    delete doc;
}