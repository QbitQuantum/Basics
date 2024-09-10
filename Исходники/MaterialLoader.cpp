	virtual void compileResource(const char* fileName, std::map<std::string, std::string>& options) {
		TiXmlDocument document;
		document.LoadFile(fileName);

		if(document.Error()) {
			throw Exception(document.ErrorDesc());
		}

		TiXmlElement* rootMaterial = document.RootElement();
		if(strcmp("material", rootMaterial->Value()) != 0) {
			throw Exception("");
		}

		TiXmlElement* xmlEffect = rootMaterial->FirstChildElement("effect");
		if(!xmlEffect)
			throw Exception("");

		const char* effectSrc = xmlEffect->Attribute("src");
		std::string effectName = file::getFilename(effectSrc);

		compiler->compile(effectSrc, options);
		Effect* effect = (Effect*)manager->loadResource(EffectKey(effectName));

		Material* material = new Material(file::getFilename(fileName), manager, effect);

		TiXmlElement* xmlSampler = xmlEffect->FirstChildElement("sampler");
		while(xmlSampler) {
			const char* samplerName = xmlSampler->Attribute("name");
			const char* textureSrc = xmlSampler->Attribute("src");
			std::string textureName = file::getFilename(textureSrc);

			compiler->compile(textureSrc, options);

			Image* image = (Image*)manager->loadResource(ImageKey(textureName));
			material->addSampler(samplerName, image);

			xmlSampler = xmlSampler->NextSiblingElement("sampler");
		}

		std::string outputName = file::getPath(fileName) + "/" + file::getFilename(fileName) + ".material";
		FileStream fileStream(outputName);
		ResourceBinStream resourceStream(fileStream);
		MaterialUtils::write(resourceStream, *manager, material);

		delete material;
	}