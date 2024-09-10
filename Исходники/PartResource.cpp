void PartResource::readMesh(slim::XmlNode* node, void* param0, void* param1, const slim::Char* meshAttrName)
{
	assert(node != NULL);

	slim::XmlAttribute* filenameAttr = node->findAttribute(meshAttrName);
	if (filenameAttr == NULL)
	{
		return;
	}
	ResourceType resType;
	slim::XmlAttribute* typeAttr = node->findAttribute(GT("type"));
	if (typeAttr != NULL && Strcmp(typeAttr->getValue<const Char*>(), GT("skinned")) == 0)
	{
		resType = RES_TYPE_SKINNED_MESH;
	}
	else
	{
		resType = RES_TYPE_RIGID_MESH;
	}
	IResource* resource = grabChildResource(resType, filenameAttr->getValue<const Char*>(), param0, param1);
	m_meshResource = static_cast<Resource*>(resource);
}