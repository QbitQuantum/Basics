bool JResourceManager::LoadResource(const string& resourceName)
{
	string path = /*mResourceRoot + */resourceName;

//	TiXmlDocument doc(path.c_str());
//	
//	if (!doc.LoadFile()) return false;
	
	JGE *engine = JGE::GetInstance();
	if (engine == NULL) return false;

	JFileSystem *fileSystem = JFileSystem::GetInstance();
	if (fileSystem == NULL) return false;

	if (!fileSystem->OpenFile(path.c_str())) return false;

	int size = fileSystem->GetFileSize();
	char *xmlBuffer = new char[size];
	fileSystem->ReadFile(xmlBuffer, size);

	TiXmlDocument doc;
	doc.Parse(xmlBuffer);

	TiXmlNode* resource = 0;
	TiXmlNode* node = 0;
	TiXmlElement* element = 0;

	resource = doc.FirstChild("resource"); 
	if (resource)
	{
		element = resource->ToElement();
		printf("---- Loading %s:%s\n", element->Value(), element->Attribute("name"));

		for (node = resource->FirstChild(); node; node = node->NextSibling())
		{
			element = node->ToElement();
			if (element != NULL)
			{
				if (strcmp(element->Value(), "texture")==0)
				{
					CreateTexture(element->Attribute("name"));
				}
				else if (strcmp(element->Value(), "quad")==0)
				{
					string quadName = element->Attribute("name");
					string textureName = element->Attribute("texture");
					float x = 0.0f;
					float y = 0.0f;
					float width = 16.0f;
					float height = 16.0f;
					float value;
					float hotspotX = 0.0f;
					float hotspotY = 0.0f;
					
					if (element->QueryFloatAttribute("x", &value) == TIXML_SUCCESS)
						x = value;
					
					if (element->QueryFloatAttribute("y", &value) == TIXML_SUCCESS)
						y = value;

					if (element->QueryFloatAttribute("width", &value) == TIXML_SUCCESS)
						width = value;

					if (element->QueryFloatAttribute("height", &value) == TIXML_SUCCESS)
						height = value;

					if (element->QueryFloatAttribute("w", &value) == TIXML_SUCCESS)
						width = value;

					if (element->QueryFloatAttribute("h", &value) == TIXML_SUCCESS)
						height = value;

					if (element->QueryFloatAttribute("hotspot.x", &value) == TIXML_SUCCESS)
						hotspotX = value;
					else
						hotspotX = width/2;

					if (element->QueryFloatAttribute("hotspot.y", &value) == TIXML_SUCCESS)
						hotspotY = value;
					else
						hotspotY = height/2;

// 					if (element->QueryFloatAttribute("regx", &value) == TIXML_SUCCESS)
// 						hotspotX = width/2;
// 
// 					if (element->QueryFloatAttribute("regy", &value) == TIXML_SUCCESS)
// 						hotspotY = height/2;
				
					int id = CreateQuad(quadName, textureName, x, y, width, height);
					if (id != INVALID_ID)
					{
						GetQuad(id)->SetHotSpot(hotspotX, hotspotY);
					}
				}
				else if (strcmp(element->Value(), "font")==0)
				{
				}
				else if (strcmp(element->Value(), "music")==0)
				{
					LoadMusic(element->Attribute("name"));
				}
				else if (strcmp(element->Value(), "sample")==0)
				{
					LoadSample(element->Attribute("name"));
				}
// 				else if (strcmp(element->Value(), "effect")==0)
// 				{
// 					RegisterParticleEffect(element->Attribute("name"));
// 				}
// 				else if (strcmp(element->Value(), "motion_emitter")==0)
// 				{
// 					RegisterMotionEmitter(element->Attribute("name"));
// 				}
			}
		}
		
	}
	
	fileSystem->CloseFile();
	delete[] xmlBuffer;
//	JGERelease();

	return true;
}