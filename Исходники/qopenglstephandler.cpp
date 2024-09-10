	QOpenGLSceneNode* load()
	{
		Handle(TDocStd_Document) doc;
		XCAFApp_Application::GetApplication()->NewDocument("MDTV-XCAF", doc);
		const QString format = m_fileName.mid(m_fileName.lastIndexOf('.')+1).toLower();
		if("stp" == format || "step" == format){
			m_format = STEPFlag;
			STEPCAFControl_Reader reader;
			reader.SetColorMode(true);
			reader.SetNameMode(true);
			reader.ReadFile(m_fileName.toUtf8().constData());
			if(reader.Transfer(doc))
				brepToNode(*doc);
		}else if("igs" == format || "iges" == format){
			m_format = IGESFlag;
			IGESCAFControl_Reader reader;
			reader.SetColorMode(true);
			reader.SetNameMode(true);
			reader.ReadFile(m_fileName.toUtf8().constData());
			if(reader.Transfer(doc))
				brepToNode(*doc);
		}
		return m_root;
	}