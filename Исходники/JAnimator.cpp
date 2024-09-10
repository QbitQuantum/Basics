bool JAnimator::Load(const char* scriptFile)
{

    JFileSystem *fileSystem = JFileSystem::GetInstance();
    if (fileSystem == NULL) return false;

    if (!fileSystem->OpenFile(scriptFile)) return false;

    int size = fileSystem->GetFileSize();
    char *xmlBuffer = new char[size];
    fileSystem->ReadFile(xmlBuffer, size);

    TiXmlDocument doc;
    doc.Parse(xmlBuffer);

    TiXmlNode* script = 0;
    TiXmlNode* frame = 0;
    TiXmlNode* obj = 0;
    TiXmlNode* param = 0;
    TiXmlElement* element = 0;

    float defaultTime = 0.033f;

    script = doc.FirstChild("script");
    if (script)
    {
        element = script->ToElement();
        printf("---- Loading %s:%s\n", element->Value(), element->Attribute("name"));

        char *type[] =
        {
            "ANIMATION_TYPE_LOOPING",
            "ANIMATION_TYPE_ONCE_AND_STAY",
            "ANIMATION_TYPE_ONCE_AND_BACK",
            "ANIMATION_TYPE_ONCE_AND_GONE",
            "ANIMATION_TYPE_PINGPONG"
        };

        const char* aniType = element->Attribute("type");
        for (int i=0; i<5; i++)
            if (strcmp(type[i], aniType)==0)
            {
                SetAnimationType(i);
                break;
            }

        float fps;
        if (element->QueryFloatAttribute("framerate", &fps) != TIXML_SUCCESS)
            fps = 30.0f;

        defaultTime = 1/fps;

        for (frame = script->FirstChild("frame"); frame; frame = frame->NextSibling())
        {
            JAnimatorFrame *aniFrame = new JAnimatorFrame(this);

            float duration;
            element = frame->ToElement();
            if (element->QueryFloatAttribute("time", &duration) != TIXML_SUCCESS)
                duration = defaultTime;
            aniFrame->SetFrameTime(duration);

            for (obj = frame->FirstChild(); obj; obj = obj->NextSibling())
            {
                for (param = obj->FirstChild(); param; param = param->NextSibling())
                {

                    element = param->ToElement();
                    if (element != NULL)
                    {
                        if (strcmp(element->Value(), "settings")==0)
                        {
                            const char* quadName = element->Attribute("quad");
                            JQuad* quad = mResource->GetQuad(quadName);

                            float x, y;
                            float vsize, hsize;
                            float angle;
                            int a, r, g, b;
                            int value;
                            bool flipped = false;

                            if (element->QueryFloatAttribute("x", &x) != TIXML_SUCCESS)
                                x = 0.0f;

                            if (element->QueryFloatAttribute("y", &y) != TIXML_SUCCESS)
                                y = 0.0f;

                            if (element->QueryFloatAttribute("hsize", &hsize) != TIXML_SUCCESS)
                                hsize = 1.0f;

                            if (element->QueryFloatAttribute("vsize", &vsize) != TIXML_SUCCESS)
                                vsize = 1.0f;

                            if (element->QueryFloatAttribute("rotation", &angle) != TIXML_SUCCESS)
                                angle = 0.0f;

                            if (element->QueryIntAttribute("a", &a) != TIXML_SUCCESS)
                                a = 255;

                            if (element->QueryIntAttribute("r", &r) != TIXML_SUCCESS)
                                r = 255;

                            if (element->QueryIntAttribute("g", &g) != TIXML_SUCCESS)
                                g = 255;

                            if (element->QueryIntAttribute("b", &b) != TIXML_SUCCESS)
                                b = 255;

                            if (element->QueryIntAttribute("flip", &value) == TIXML_SUCCESS)
                                flipped = (value==1);


                            JAnimatorObject *object = new JAnimatorObject();
                            object->SetQuad(quad);
                            object->SetPosition(x, y);
                            object->SetHScale(hsize);
                            object->SetVScale(vsize);
                            object->SetRotation(angle);
                            object->SetColor(ARGB(a,r,g,b));
                            object->SetFlip(flipped);

                            aniFrame->AddObject(object);

                        }
                    }
                }

            }

            mFrames.push_back(aniFrame);
        }

    }

    fileSystem->CloseFile();
    delete[] xmlBuffer;

    return true;

}