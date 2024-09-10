int Blockporter::DoExport(const TCHAR* name, ExpInterface* ei, Interface* i, BOOL supressPrompts, DWORD options)
{
	INode* root;
	//caption and message for MessagesBoxes
	TCHAR msg[MB_BUFFER_LENGTH];
	TCHAR cap[MB_BUFFER_LENGTH];

	//Get the root node
	root = i->GetRootNode();

	//the node of our object should be a groupnode, which contains every object
	//we want to export
	i->PushPrompt(_T("Searching for Group..."));
	bool found = false;
	for(int idx = 0; idx < root->NumberOfChildren(); idx++)
	{
		if(root->GetChildNode(idx)->IsGroupHead())
		{
			//we found our group
			//next step is to make the group node our new root, because every object
			//we want is part of this group

			found = true;
			root = root->GetChildNode(idx);
			break;
		}
	}

	if(!found)
	{
		MessageBox(nullptr, GetString(IDS_ERROR_NO_GROUP, msg), GetString(IDS_GENERAL_ERROR, cap), MB_OK | MB_ICONERROR);
		return 0;
	}

	//Now that we have the groupnode let's compare the fileversions
	if(!IsNewModelVersion(name, root->GetName()))
	{
		if(MessageBox(nullptr, GetString(IDS_VER_TO_LOW_MSG, msg), GetString(IDS_VER_TO_LOW_CAP, cap), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
			return 1;
	}

	i->PushPrompt(_T("Opening File"));
	Interface14* iface = GetCOREInterface14();
	UINT code = iface->DefaultTextSaveCodePage(true);
	MaxSDK::Util::Path storageNamePath(name);
	storageNamePath.SaveBaseFile();
	switch (code & MaxSDK::Util::MaxStringDataEncoding::MSDE_CP_MASK)
	{
	case CP_UTF8:
		mStream = _tfopen(name, _T("wt, ccs=UFT-8"));
		break;
	case MaxSDK::Util::MaxStringDataEncoding::MSDE_CP_UTF16:
		mStream = _tfopen(name, _T("wt, ccs=UTF-16BE"));
		break;
	default:
		mStream = _tfopen(name, _T("wt"));
	}
	if(!mStream)
		return 0;

	//now we have our file stream, so let's write the header
	i->PushPrompt(_T("Writing Header"));
	WriteHeader(root->GetName(), root->NumberOfChildren());

	//now that we have the header written, let's iterate through the objects in the
	//group and export the meshes and lights

	INode* child;
    Point3 pMin(0,0,0), pMax(0,0,0);

	for(int idx = 0; idx < root->NumberOfChildren(); idx++)
	{
		child = root->GetChildNode(idx);
		i->PushPrompt(_T("Processing Object %s", child->GetName()));
		if(child->IsGroupHead())
		{
			MessageBox(nullptr, GetString(IDS_ERROR_TO_MANY_GROUPS, msg), GetString(IDS_GENERAL_ERROR, cap), MB_OK | MB_ICONERROR);
			continue;
		}

		ObjectState os = child->EvalWorldState(0);

		//let's take a look at the SuperClassID of the object
		//so we find out if it's a mesh or a light
		if(!os.obj)
			continue; //somehow this node doesn't have an object

        Box3 boundBox;

		switch(os.obj->SuperClassID())
		{
		case GEOMOBJECT_CLASS_ID:
			_ftprintf(mStream, _T("<ObjectID=%i>\n"), idx);
			i->PushPrompt(_T("Writing MeshData for Object %s", child->GetName()));
			boundBox = WriteMeshData(child, idx);
            pMin.x = (boundBox.Min().x < pMin.x) ? boundBox.Min().x : pMin.x;
            pMin.y = (boundBox.Min().y < pMin.y) ? boundBox.Min().y : pMin.y;
            pMax.x = (boundBox.Max().x > pMax.x) ? boundBox.Max().x : pMax.x;
            pMax.y = (boundBox.Max().y > pMax.y) ? boundBox.Max().y : pMax.y;
			i->PushPrompt(_T("Writing MaterialData for Object %s", child->GetName()));
			WriteMaterialData(child);
			_ftprintf(mStream, _T("</Object>\n"));
			break;
		//case LIGHT_CLASS_ID:
		//	WriteLightData(child, idx);
		//	break;
		}
	}

    //Write the Bounding Box
    _ftprintf(mStream, _T("<BoundingBox>\n"));
    _ftprintf(mStream, _T("\t<Min=%f,%f>\n"), pMin.x, pMin.y);
    _ftprintf(mStream, _T("\t<Max=%f,%f>\n"), pMax.x, pMax.y);
    _ftprintf(mStream, _T("</BoundingBox>\n"));
	//we are done exporting, so close the stream
	i->PushPrompt(_T("Closing file..."));
	fclose(mStream);

	MessageBox(nullptr, GetString(IDS_FINISH_MSG, msg), GetString(IDS_FINISH_CAP, cap), MB_OK | MB_ICONINFORMATION);

	return 1;
}