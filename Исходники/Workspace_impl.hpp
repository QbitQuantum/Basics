    void Workspace<EncodingT>::loadXML(DOMElement* xml_wrks)
    {
        DOMElement*  xml_file       = NULL;
        DOMText*     xml_text       = NULL;
        DOMNodeList* xml_list       = NULL;

        if (!xml_wrks || string("Workspace") != A(xml_wrks->getTagName()))
        {
            m_logger->fatalStream() << "Workspace::loadXML() : XML workspace element expected";
            //throw BadXmlFormatException("XML entity element expected");
        }
        else {
            m_name = C(xml_wrks->getAttribute( AX("Name") ));
            m_author = C(xml_wrks->getAttribute( AX("Author") ));
            m_brief = C(xml_wrks->getAttribute( AX("Brief") ));
            m_version = C(xml_wrks->getAttribute( AX("Version") ));
            m_type = (A(xml_wrks->getAttribute( AX("Type") ))==string("File"))?WRK_FILE:WRK_PROJECT;
            m_option = ToInt::parse(A(xml_wrks->getAttribute( AX("Option") )));
            m_comment = EncodingT::EMPTY;
            m_files.clear();
            if (xml_wrks->hasChildNodes())
            {
                 xml_list = xml_wrks->getChildNodes();
                 for (unsigned int i=0; i<xml_list->getLength(); ++i)
                 {
                     xml_file = (DOMElement*) xml_list->item(i);
                     if (xml_file && string("File") == A(xml_file->getTagName()))
                     {
                         File<EncodingT> fi;
                         fi.loadXML(xml_file);
                         m_files.push_back(fi);
                     }

                     if (xml_file && string("Comments") == A(xml_file->getTagName()))
                     {
                        try 
                        {
                            xml_text = (DOMText*) xml_file->getFirstChild();
                            if (xml_text)
                            {
                                m_comment = C(xml_text->getData());
                            }
                        } 
                        catch(DOMException & e) 
                        {
                            m_logger->fatalStream() << "Workspace::loadXML() : XML wrk comments element error: " 
                                                    << A(e.getMessage());
                            //throw e;
                        }
                     }
                 }
            }
            // Add wokspace file if it is not defined.
            if (m_type==WRK_FILE && 
                (m_files.empty()  || 
                 sizeFiles() != 1 || 
                 beginFiles()->getName() != getName()))
            {
                openFile(getName(), true);
            }
            m_logger->debugStream() << "set workspace : "
                                    << encode<EncodingT,ansi>(m_name) << ", "
                                    << encode<EncodingT,ansi>(m_comment);
            m_logger->debug("Workspace::loadXML() : XML workspace loaded");
        }
    }