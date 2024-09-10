	/*! Ctor.
	  \param xmlfile xml config filename.
	  \param do_process if true, process the file on construction */
	Configuration(const std::string& xmlfile, bool do_process=false)
		: _xmlfile(xmlfile), _root(XmlElement::Factory(_xmlfile)) { if (do_process) process(); }