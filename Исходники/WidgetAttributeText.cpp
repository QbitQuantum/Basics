status_t
WidgetAttributeText::AttrAsString(const Model* model, BString* outString,
	const char* attrName, int32 attrType, float width, BView* view,
	int64* resultingValue)
{
	int64 value;

	status_t error = model->InitCheck();
	if (error != B_OK)
		return error;

	switch (attrType) {
		case B_TIME_TYPE:
			if (strcmp(attrName, kAttrStatModified) == 0)
				value = model->StatBuf()->st_mtime;
			else if (strcmp(attrName, kAttrStatCreated) == 0)
				value = model->StatBuf()->st_crtime;
			else {
				TRESPASS();
				// not yet supported
				return B_ERROR;
			}
			TruncTimeBase(outString, value, view, width);
			if (resultingValue)
				*resultingValue = value;

			return B_OK;

		case B_STRING_TYPE:
			if (strcmp(attrName, kAttrPath) == 0) {
				BEntry entry(model->EntryRef());
				BPath path;
				BString tmp;

				if (entry.InitCheck() == B_OK
					&& entry.GetPath(&path) == B_OK) {
					tmp = path.Path();
					TruncateLeaf(&tmp);
				} else
					tmp = "-";

				if (width > 0) {
					TruncStringBase(outString, tmp.String(), tmp.Length(), view,
						width);
				} else
					*outString = tmp.String();

				return B_OK;
			}
			break;

		case kSizeType:
//			TruncFileSizeBase(outString, model->StatBuf()->st_size, view,
//				width);
			return B_OK;
			break;

		default:
			TRESPASS();
			// not yet supported
			return B_ERROR;

	}

	TRESPASS();
	return B_ERROR;
}