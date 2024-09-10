bool
ResourceData::SetFromResource(const int32 &index, BResources &res)
{
	char *name;
	if (!res.GetResourceInfo(index, (type_code*)&fType, &fID,
							(const char **)&name, &fLength)) {
		*this = ResourceData();
		return false;
	}
	fName = name;
	fTypeString = MakeTypeString(fType);
	fIDString = "";
	fIDString << fID;
	fAttr = false;
	char *data = (char *)res.LoadResource(fType,fID,&fLength);
	SetData(data,fLength);
	
	return true;
}